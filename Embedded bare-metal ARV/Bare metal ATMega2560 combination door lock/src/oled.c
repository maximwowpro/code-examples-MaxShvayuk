/* MIT License
 * 
 * Copyright 2018, Tymofii Khodniev <thodnev @ github>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

#include "oled.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if !defined(OLED_NO_I2C)
/***** I2C-related logic *****/
uint8_t OLED_cmdbuffer[OLED_CMDBUFFER_LEN];

static uint8_t _i2c_cmd_init[] = {
	0x80, 0x8D, 0x80, 0x14	/* Enable charge pump	 */
	,0x80, 0xAF		/* Display on	      	 */
	,0x80, 0x81, 0x80, 0xFF /* Set brightness to 255 */
	,0x80, 0xA7		/* Enable inversion 	 */
};

static uint8_t _i2c_cmd_setpage[] = {
	0x80, 0x00, 0x80, 0x10, /* Set column cursor to 0 */
	0x80, 0xB0 /* Last nibble in 0xB0 defines page (0xB0..0xB7) */
};

static uint8_t _i2c_cmd_setbrightness[] = {
	0x80, 0x81, 0x80, 0xFF  /* Last byte is brightness level (0..255) */
};

static uint8_t _i2c_cmd_dataprefix[] = {0x40};

static uint8_t i2c_devaddr;
static uint8_t *i2c_prefix_ptr;
static uint8_t *i2c_prefix_count;
static uint8_t *i2c_data_ptr;
static uint16_t i2c_data_count;
static bool i2c_is_fastfail;
static void (*i2c_callback)(void *); /* called after transaction finish */
static void *i2c_callback_args;

/* States used in ISR FSM */
enum I2C_State_e {
	I2C_STATE_IDLE = 0,
	I2C_STATE_STOP,
	I2C_STATE_SLAVEADDR,
	I2C_STATE_WRITEPREFIX,
	I2C_STATE_WRITEBYTE
};
static enum I2C_State_e i2c_state = I2C_STATE_IDLE;


static void I2C_init(uint32_t hz_freq)
{
	i2c_state = I2C_STATE_IDLE;
	/* Enable the Two Wire Interface module */
	power_twi_enable();

	/* Select TWBR and TWPS based on frequency. Quite tricky, the main point */
	/* is that prescaler is a pow(4, TWPS)				 	 */
	/* TWBR * TWPS_prescaler value */
	uint32_t twbr = F_CPU / (2 * hz_freq) - 8;
	uint8_t twps;
	for (twps = 0; twps < 4; twps++) {
		if (twbr <= 255)
			break;
		twbr /= 4;
	}

	TWBR = (uint8_t)twbr;
	TWSR = (TWSR & 0xFC) | (twps & 0x03);

	TWCR = (1 << TWEN) | (1 << TWIE);
}


bool OLED_i2c_tx_shed(uint8_t addr, uint8_t *prefix, uint8_t prefix_len, uint8_t *bytes, uint16_t bytes_len, 
		      void (*end_cbk)(void *), void *cbk_args, bool fastfail)
{
	bool ret = false;
	/* No interrupts can occur while this block is executed */
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (i2c_state == I2C_STATE_IDLE) {
			i2c_prefix_ptr = prefix;
			i2c_prefix_count = prefix_len;
			i2c_data_ptr = bytes;
			i2c_data_count = bytes_len;
			i2c_is_fastfail = fastfail;
			i2c_callback = end_cbk;
			i2c_callback_args = cbk_args;
			/* Send START signal and initiating new transaction */
			i2c_state = I2C_STATE_SLAVEADDR;
			i2c_devaddr = (addr << 1);
			TWCR |= (1 << TWSTA) | (1 << TWINT);
			ret = true;
		}
	}
	return ret;
}


ISR(TWI_vect, ISR_BLOCK)
{
	switch(i2c_state) {
	case(I2C_STATE_IDLE):
	case(I2C_STATE_STOP):
		/* transfer stop and go to IDLE*/
		/* signal with callback that transaction is over */
		TWCR |= (1 << TWSTO) | (1 << TWINT);
		i2c_state = I2C_STATE_IDLE;
		(*i2c_callback)(i2c_callback_args);
		break;
	case(I2C_STATE_SLAVEADDR):
		// load value
		TWDR = i2c_devaddr;
		TWCR = (TWCR & ~(1 << TWSTA)) | (1 << TWINT);
		if ((NULL == i2c_prefix_ptr) && (NULL == i2c_data_ptr)) {
			i2c_state = I2C_STATE_STOP;
		} else if (NULL == i2c_prefix_ptr) {
			i2c_state = I2C_STATE_WRITEBYTE;
		} else {
			i2c_state = I2C_STATE_WRITEPREFIX;
		}
		break;
	case(I2C_STATE_WRITEPREFIX):
		// load next byte of prefix
		TWDR = *i2c_prefix_ptr++;
		i2c_prefix_count--;
		TWCR |= (1 << TWINT);
		if (!i2c_prefix_count) {
			i2c_state = (NULL == i2c_data_ptr) ? I2C_STATE_STOP : I2C_STATE_WRITEBYTE;
		}
		break;
	case(I2C_STATE_WRITEBYTE):
		// load next byte
		TWDR = *i2c_data_ptr++;
		i2c_data_count--;
		TWCR |= (1 << TWINT);
		if (!i2c_data_count)
			i2c_state = I2C_STATE_STOP;
		break;
	}
}


/* Callback which essentially does nothing */
static void OLED_cbk_empty(void *args)
{
	// empty callback
}


/* A dummy callback which simply unlocks the oled lock */
static void OLED_cbk_unlock(void *args)
{
	OLED *oled = args;
	OLED_unlock(oled);
}


/* Callbacks which are used to write each page */
static void OLED_cbk_writepage(void *args);
static void OLED_cbk_setwritepage(void *args);
/* Writes page. This is called after OLED_cbk_setwritepage */
static void OLED_cbk_writepage(void *args)
{
	OLED *oled = args;
	if (oled->cur_page >= oled->num_pages) {
		OLED_unlock(oled);
		return;
	}
	uint8_t *lineptr = &oled->frame_buffer[oled->cur_page * (uint16_t)oled->width];
	oled->cur_page++;
	while(!OLED_i2c_tx_shed(oled->i2c_addr, _i2c_cmd_dataprefix, OLED_ARR_SIZE(_i2c_cmd_dataprefix), 
				lineptr, oled->width,
				&OLED_cbk_setwritepage, oled, true)) {
		// nop
	}
}

/* Sets page index and calls OLED_cbk_writepage via callback */
static void OLED_cbk_setwritepage(void *args)
{
	OLED *oled = args;
	_i2c_cmd_setpage[OLED_ARR_SIZE(_i2c_cmd_setpage) - 1] = 0xB0 | oled->cur_page;
	while(!OLED_i2c_tx_shed(oled->i2c_addr, _i2c_cmd_setpage, 
                                OLED_ARR_SIZE(_i2c_cmd_setpage), NULL, 0,
				&OLED_cbk_writepage, oled, true)) {
		// nop
	}
}



void OLED_cmd_setbrightness(OLED *oled, uint8_t level)
{
	_i2c_cmd_setbrightness[OLED_ARR_SIZE(_i2c_cmd_setbrightness) - 1] = level;
	OLED_spinlock(oled);
	while(!OLED_i2c_tx_shed(oled->i2c_addr, _i2c_cmd_setbrightness, 
                                OLED_ARR_SIZE(_i2c_cmd_setbrightness), NULL, 0,
				&OLED_cbk_unlock, oled, true)) {
		// nop
	}
}


void OLED_refresh(OLED *oled)
{
	OLED_spinlock(oled);
	/* Code below is executed under lock */
	oled->cur_page = 0;
	OLED_cbk_setwritepage(oled);
	/* Lock is unlocked after series of callbacks, in the last one */
}
#endif // OLED_NO_I2C


/***** Display-related logic *****/
OLED_err __OLED_init(OLED *oled, uint8_t width, uint8_t height, uint8_t *frame_buffer, uint32_t i2c_freq_hz, uint8_t i2c_addr)
{
	oled->width = width;
	oled->height = height;
	oled->frame_buffer = frame_buffer;
	oled->busy_lock = 1;	/* Initially: 1 - unlocked */

	OLED_I2CWRAP(
		oled->i2c_addr = i2c_addr;
		oled->cur_page = 0;
		oled->num_pages = 8;

		I2C_init(i2c_freq_hz);
		
		if (!OLED_i2c_tx_shed(oled->i2c_addr, _i2c_cmd_init, OLED_ARR_SIZE(_i2c_cmd_init),
				      NULL, 0, OLED_cbk_empty, NULL, true)) {
			return OLED_EBUSY;
		}
	) // OLED_I2CWRAP

	return OLED_EOK;
}


OLED_err OLED_put_pixel(OLED *oled, uint8_t x, uint8_t y, bool pixel_state)
{
	if ((x >= oled->width) || (y >= oled->height))
		return OLED_EBOUNDS;
	OLED_put_pixel_(oled, x, y, pixel_state);	/* Use inline */
	return OLED_EOK;
}


OLED_err OLED_put_rectangle(OLED *oled, uint8_t x_from, uint8_t y_from, uint8_t x_to, uint8_t y_to, enum OLED_params params)
{
	if (params > (OLED_BLACK | OLED_FILL))
		return OLED_EPARAMS;
	bool pixel_color = (OLED_BLACK & params) != 0;
	bool is_fill = (OLED_FILL & params) != 0;

	/* Limit coordinates to display bounds */
	uint8_t size_errors = 0;
	uint8_t w_max = oled->width - 1;
	uint8_t h_max = oled->height - 1;
	if (x_from > w_max) {
		x_from = w_max;
		size_errors++;
	}
	if (x_to > w_max) {
		x_to = w_max;
		size_errors++;
	}
	if (y_from > h_max) {
		y_from = h_max;
		size_errors++;
	}
	if (y_to > h_max) {
		y_to = h_max;
		size_errors++;
	}
	/* If all coordinates are out of bounds */
	if (size_errors >= 4)
		return OLED_EBOUNDS;

	//OLED_WITH_SPINLOCK(oled) {
		/* Normalize coordinates */
		/* start_@ indicates coordinates of upper left corner  */
		/* stop_@ indicates coordinates of bottom right corner */
		uint8_t start_x = x_to < x_from ? x_to : x_from; /* x min */
		uint8_t start_y = y_to < y_from ? y_to : y_from; /* y min */
		uint8_t stop_x = x_to > x_from ? x_to : x_from;  /* x max */
		uint8_t stop_y = y_to > y_from ? y_to : y_from;  /* y max */

		if (is_fill) {
			/* Fill whole area */
			for (uint8_t x = start_x; x <= stop_x; x++) {
				for (uint8_t y = start_y; y <= stop_y; y++) {
					OLED_put_pixel_(oled, x, y, pixel_color);
				}
			}
		} else {
			/* Draw outer frame */
			for (uint8_t x = start_x; x <= stop_x; x++) {
				OLED_put_pixel_(oled, x, start_y, pixel_color);
				OLED_put_pixel_(oled, x, stop_y, pixel_color);
			}
			for (uint8_t y = start_y; y <= stop_y; y++) {
				OLED_put_pixel_(oled, start_x, y, pixel_color);
				OLED_put_pixel_(oled, stop_x, y, pixel_color);
			}
		}
	//}

	return OLED_EOK;
}


OLED_err OLED_put_line(OLED *oled, uint8_t x_from, uint8_t y_from, uint8_t x_to, uint8_t y_to, enum OLED_params params)
{
	if (params > (OLED_BLACK | OLED_FILL))
		return OLED_EPARAMS;
	bool pixel_color = (OLED_BLACK & params) != 0;
	
	/* Limit coordinates to display bounds */
	uint8_t size_errors_x = 0;
	uint8_t size_errors_y = 0;
	uint8_t w_max = oled->width - 1;
	uint8_t h_max = oled->height - 1;
	if (x_from > w_max) {
		x_from = w_max;
		size_errors_x++;
	}
	if (x_to > w_max) {
		x_to = w_max;
		size_errors_x++;
	}
	if (y_from > h_max) {
		y_from = h_max;
		size_errors_y++;
	}
	if (y_to > h_max) {
		y_to = h_max;
		size_errors_y++;
	}
	/* If we can't draw the line at display */
	if (size_errors_x >= 2 || size_errors_y >= 2 )
		return OLED_EBOUNDS;
	

	/* Work with coordinates:
	 * 
	* There may be 4 situations:
	* 1) start - top    left  ; end - bottom right
	* 2) start - bottom right ; end - top    left
	* 3) start - top    right ; end - bottom left
	* 4) start - bottom left  ; end - top    right
	*/

	uint8_t start_x = x_from; 
	uint8_t start_y = y_from; 
	uint8_t stop_x = x_to;     
	uint8_t stop_y = y_to;    
	
	/* This code has handlers only for situation_1 and situation_4, so
	 * if we have situation_2 or situation_3 - convert them to situation_1 or situation_4 
	 */
	if ( (x_from >= x_to && y_from >= y_to)
	  || (x_from >  x_to && y_from <  y_to) ) {
		start_x = x_to;
		start_y = y_to;
		stop_x = x_from;
		stop_y = y_from;
	}
	
	/* If the line is horizontal */
	if (start_y == stop_y) {
		for (uint8_t x = start_x; x <= stop_x; x++)
			OLED_put_pixel_(oled, x, start_y, pixel_color);
		return OLED_EOK;
	}
	
	/* If the line is vertical */
	if (start_x == stop_x) {
		for (uint8_t y = start_y; y <= stop_y; y++)
			OLED_put_pixel_(oled, start_x, y, pixel_color);
		return OLED_EOK;
	}

	/* If the line is  45-degrees inclined line */
	if ( (stop_x - start_x == start_y - stop_y)
	  && (start_x < stop_x && start_y > stop_y) ) {		/* situation_4 handler */
		uint8_t x = start_x, y = start_y;
		for (; x <= stop_x; x++, y--)
			OLED_put_pixel_(oled, x, y, pixel_color);
		return OLED_EOK;
	} else if (stop_x - start_x == stop_y - start_y) {	/* situation_1 handler */
		uint8_t x = start_x, y = start_y;
		for (; x <= stop_x && y <= stop_y; x++, y++)
				OLED_put_pixel_(oled, x, y, pixel_color);
		return OLED_EOK;
	}
	
	/* If the line is inclined in NOT 45 degrees*/
	uint8_t delta_small = 0;
	uint8_t delta_big   = 0;
	
	if (start_x < stop_x && start_y < stop_y) { 	  	/* situation_1 handler */
		if (stop_x - start_x > stop_y - start_y) {
			delta_big = stop_x - start_x;
			delta_small = stop_y - start_y;
		} else if (stop_x - start_x < stop_y - start_y) {
			delta_big = stop_y - start_y;
			delta_small = stop_x - start_x;
		}
	} else if (start_x < stop_x && start_y > stop_y) { 	/* situation_4 handler */
		if (stop_x - start_x > start_y - stop_y) {
			delta_big = stop_x - start_x;
			delta_small = start_y - stop_y;
		} else if (stop_x - start_x < start_y - stop_y) {
			delta_big = start_y - stop_y;
			delta_small = stop_x - start_x;
		}
	}
	
	/* In the matrix-like display we can't draw inclined line, 
	 * but we can represent it in the form of stairs, 
	 * which will approximated to inclined line by human's vision.
	 * num_lines is a number of this stairs (6 in Example).
	 * num_lines = delta_small
	 * Example:
	 * 000000
	 *       000000
	 * 	       00000
	 * 	            000000
	 * 		          000000
	 * 		                00000
	 * is approximated form of inclined line.
	 */
	
	/* There can be 2 situations:
	 * - delta_big % delta_small == 0
	 * - delta_big % delta_small != 0
	 * In the first case the lenght of every line (stair) == delta_big / delta_small.
	 */
	uint8_t line_lenght = delta_big / delta_small; /* line_lenght means short_line lenght */
	
	/* Now we work with first case (delta_big % delta_small == 0) */
	if (delta_big % delta_small == 0) {
		if (start_x < stop_x && start_y < stop_y) { 	  	/* situation_1 handler */
			if (delta_small == stop_x - start_x) {
				uint8_t x = 0, y = 0;
				for (; y <= delta_big; y++) {
					if (0 == y % line_lenght)
						x++;
					OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
				}
				return OLED_EOK;
			}
			if (delta_small == stop_y - start_y) {
				uint8_t x = 0, y = 0;
				for (; x <= delta_big; x++) {
					if (0 == x % line_lenght)
						y++;
					OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
				}
				return OLED_EOK;
			}
		} else if (start_x < stop_x && start_y > stop_y) { 	/* situation_4 handler */
			if (delta_small == stop_x - start_x) {
				uint8_t x = 0, y = 0;
				for (; y <= delta_big; y++) {
					if (0 == y % line_lenght)
						x++;
					OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
				}
				return OLED_EOK;
			}
			if (delta_small == start_y - stop_y) {
				uint8_t x = 0, y = 0;
				for (; x <= delta_big; x++) {
					if (0 == x % line_lenght)
						y++;
					OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
				}
				return OLED_EOK;
			}
		}
	}
	
	/* Now we work with second case (delta_big % delta_small != 0)
	 * In the second case we will have lines with two different lenghts:
	 * - short_line lenght = delta_big / delta_small
	 * - long_line  lenght = delta_big / delta_small + 1
	 * Number of long_lines can be counted by such formula:
	 * num_long_lines = delta_big % delta_small
	 *
	 * Next we should determine when we must draw short_line and when long_line.
	 * long_line_pos is a line(stair) position on which we should draw short_line.
	 * the condition of drawing short_line is:
	 * if (0 == current_line_position % long_line_pos)
	 * For this stuff I use such formula:
	 * long_line_pos = delta_small / (delta_small - (delta_big % delta_small))
	 */
	uint8_t long_line_pos = delta_small / (delta_small - (delta_big % delta_small));
	
	if (start_x < stop_x && start_y < stop_y) { 	  	/* situation_1 handler */
		if (delta_small == stop_x - start_x) {
			uint8_t x = 0, y = 0;
			for (; y < delta_big; y++) {
				if (0 == y % line_lenght)
					x++;
				if (0 == (x + 1) % long_line_pos) {
					OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
					y++;
				}
				OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
			}
				return OLED_EOK;
		}
		if (delta_small == stop_y - start_y) {
			uint8_t x = 0, y = 0;
			for (; x < delta_big; x++) {
				if (0 == x % line_lenght)
					y++;
				if (0 == (y + 1) % long_line_pos) {
					OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
					x++;
				}
				OLED_put_pixel_(oled, start_x + x, start_y + y, pixel_color);
			}
				return OLED_EOK;
		}
	} else if (start_x < stop_x && start_y > stop_y) { 	/* situation_4 handler */
		if (delta_small == stop_x - start_x) {
			uint8_t x = 0, y = 0;
			for (; y < delta_big; y++) {
				if (0 == y % line_lenght)
					x++;
				if (0 == (x + 1) % long_line_pos) {
					OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
					y++;
				}
				OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
			}
				return OLED_EOK;
		}
		if (delta_small == start_y - stop_y) {
			uint8_t x = 0, y = 0;
			for (; x < delta_big; x++) {
				if (0 == x % line_lenght)
					y++;
				if (0 == (y + 1) % long_line_pos) {
					OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
					x++;
				}
				OLED_put_pixel_(oled, start_x + x, start_y - y, pixel_color);
			}
				return OLED_EOK;
		}
	}
	return OLED_EOK;
}



OLED_err OLED_put_triangle(OLED *oled, uint8_t point_1_x, uint8_t point_1_y, uint8_t point_2_x, uint8_t point_2_y, 
			   uint8_t point_3_x, uint8_t point_3_y, enum OLED_params params)
{
	if (params > (OLED_BLACK | OLED_FILL))
		return OLED_EPARAMS;
	bool pixel_color = (OLED_BLACK & params) != 0;
	bool is_fill = (OLED_FILL & params) != 0;
	
	if (false == is_fill) {
		OLED_WITH_SPINLOCK(oled) {
		OLED_put_line(oled, point_1_x, point_1_y, point_2_x, point_2_y, params);
		OLED_put_line(oled, point_2_x, point_2_y, point_3_x, point_3_y, params);
		OLED_put_line(oled, point_3_x, point_3_y, point_1_x, point_1_y, params);
		}
		return OLED_EOK;
	}
	
	/* Now fill the triangle.
	 * Firstly, create the rectangle, which contains our triangle .
	 * Search left, right, top and bottom sides of rectangle.
	 */
	uint8_t right = 0, left = 0, top = 0, bottom = 0;
	if (point_1_x <= point_2_x && point_1_x <= point_3_x)
		left = point_1_x;
	else if (point_2_x <= point_1_x && point_2_x <= point_3_x)
		left = point_2_x;
	else if (point_3_x <= point_1_x && point_3_x <= point_2_x)
		left = point_3_x;
	
	if (point_1_x >= point_2_x && point_1_x >= point_3_x)
		right = point_1_x;
	else if (point_2_x >= point_1_x && point_2_x >= point_3_x)
		right = point_2_x;
	else if (point_3_x >= point_1_x && point_3_x >= point_2_x)
		right = point_3_x;
	
	if (point_1_y <= point_2_y && point_1_y <= point_3_y)
		top = point_1_y;
	else if (point_2_y <= point_1_y && point_2_y <= point_3_y)
		top = point_2_y;
	else if (point_3_y <= point_1_y && point_3_y <= point_2_y)
		top = point_3_y;
	
	if (point_1_y >= point_2_y && point_1_y >= point_3_y)
		bottom = point_1_y;
	else if (point_2_y >= point_1_y && point_2_y >= point_3_y)
		bottom = point_2_y;
	else if (point_3_y >= point_1_y && point_3_y >= point_2_y)
		bottom = point_3_y;
	
	/* Now fill the triangle.
	 * For each point(pixel) identify is it inside or outside the triangle
	 * using formulas.
	 * Read about this formulas:
	 * http://www.abakbot.ru/online-2/280-pointreug
	 * http://www.cyberforum.ru/algorithms/thread144722.html
	 * http://www.cyberforum.ru/mathematics/thread8234.html
	 */
	for (uint8_t y = top; y <= bottom; y++) {
		for (uint8_t x = left; x <= right; x++) {
			int16_t r1 = (point_1_x - x) * (point_2_y - point_1_y) - (point_2_x - point_1_x) * (point_1_y - y);
			int16_t r2 = (point_2_x - x) * (point_3_y - point_2_y) - (point_3_x - point_2_x) * (point_2_y - y);
			int16_t r3 = (point_3_x - x) * (point_1_y - point_3_y) - (point_1_x - point_3_x) * (point_3_y - y);
			
			/* the point is over the side of triangle */
			if (0 == r1 * r2 * r3)
				continue;
			/* the point is inside the triangle, fill it */
			if ( (r1 < 0 && r2 < 0 && r3 < 0) || (r1 > 0 && r2 > 0 && r3 > 0) ) {
				OLED_WITH_SPINLOCK(oled) {
					OLED_put_pixel(oled, x, y, pixel_color);
				}
			}
		}
	}

	return OLED_EOK;
}


OLED_err OLED_put_elipse(OLED *oled, uint8_t x, uint8_t y, uint16_t a, uint16_t b, enum OLED_params params)
{
	if (params > (OLED_BLACK | OLED_FILL | OLED_BORDER_BLACK))
		return OLED_EPARAMS;
	
	bool pixel_border_color = params & (1<<2);
	
	bool pixel_color = params & (1<<0);
	bool is_fill = params & (1<<1);
	
	uint32_t a_2=a*a;
	uint32_t b_2=b*b;
	uint32_t ab_2=a_2*b_2;
	
	uint16_t x_cur=x;
	uint16_t y_cur=y+b;
	
	uint32_t err_move_right=0;
	uint32_t err_move_diag=0;
	uint32_t err_move_down=0;
 	uint32_t move_right=0;
	uint32_t move_diag=0;
	uint32_t move_down=0;
	
	uint8_t begin, end;
	uint8_t last_lvl_u=y+b;
	
	if(x < 128 && x >= 0 && y + b < 64 && y + b >= 0) 
		OLED_put_pixel_(oled, x, y+b, pixel_border_color); 
	if(x < 128 && x >= 0 && y - b < 64 && y - b >= 0) 
		OLED_put_pixel_(oled, x, y-b, pixel_border_color); 
	
	while(y_cur >= y)
	{	
		move_right=(((x_cur-x+1)*(x_cur-x+1))*b_2)+(((y_cur-y)*(y_cur-y))*a_2);
		move_diag=((x_cur-x+1)*(x_cur-x+1)*b_2)+(((y_cur-y-1)*(y_cur-y-1))*a_2);
		move_down=(((x_cur-x)*(x_cur-x))*b_2)+(((y_cur-y-1)*(y_cur-y-1))*a_2);
		
		err_move_right=move_right>ab_2?move_right-ab_2:ab_2-move_right;
		err_move_diag=move_diag>ab_2?move_diag-ab_2:ab_2-move_diag;
		err_move_down=move_down>ab_2?move_down-ab_2:ab_2-move_down;
		
		if(err_move_right<=err_move_diag && err_move_right<=err_move_down) {x_cur++;}
		else if(err_move_diag<=err_move_right && err_move_diag<=err_move_down) {x_cur++; y_cur--;}
		else {y_cur--;}
		
		if(x_cur<128 && x_cur>=0 && y_cur<64 && y_cur>=0) OLED_put_pixel_(oled, x_cur, y_cur, pixel_border_color);
		if(x_cur-2*(x_cur-x)<128 && x_cur-2*(x_cur-x)>=0 && y_cur<64 && y_cur>=0) OLED_put_pixel_(oled, x_cur-2*(x_cur-x), y_cur, pixel_border_color);
		if(x_cur<128 && x_cur>=0 && y_cur-2*(y_cur-y)<64 && y_cur-2*(y_cur-y)>=0) OLED_put_pixel_(oled, x_cur, y_cur-2*(y_cur-y), pixel_border_color);
		if(x_cur-2*(x_cur-x)<128 && x_cur-2*(x_cur-x)>=0 && y_cur-2*(y_cur-y)<64 && y_cur-2*(y_cur-y)>=0) OLED_put_pixel_(oled, x_cur-2*(x_cur-x), y_cur-2*(y_cur-y), pixel_border_color);
		
		if(x_cur+1>127) begin=127;
		else begin=x_cur-1;
		
		if(x_cur<x) end=0;
		else if(x_cur<2*(x_cur-x)) end=0;
		else end=x_cur-2*(x_cur-x);
		
		if(is_fill && y_cur!=y+b && last_lvl_u!=y_cur)for(uint16_t i=begin; i>end; i--)
		{
			if(y_cur<64 && y_cur>=0) { OLED_put_pixel_(oled, i, y_cur, pixel_color); }
			if(y_cur-2*(y_cur-y)<64 && y_cur-2*(y_cur-y)>=0) {OLED_put_pixel_(oled, i, y_cur-2*(y_cur-y), pixel_color);}
			last_lvl_u=y_cur;
		}
		
	}
	return OLED_EOK;
}


OLED_err OLED_draw_closed_lock(OLED *oled)
{
	OLED_WITH_SPINLOCK(oled) {
		// Clear the display
		OLED_put_rectangle(oled, 0, 0, 127, 63, OLED_FILL | 1);
			
		// L letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 5, 13, 15, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 13, 5, 30, 8, OLED_FILL | OLED_WHITE);

		// O letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 20, 30, 30, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 13, 23, 27, 27, OLED_FILL | OLED_BLACK);

		// C letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 35, 30, 45, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 13, 38, 27, 45, OLED_FILL | OLED_BLACK);
		
		// K letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 50, 30, 53, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 18, 53, 22, 55, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 16, 55, 24, 58, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 23, 57, 30, 61, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 18, 57, 10, 61, OLED_FILL | OLED_WHITE);
		
		// draw the image of lock
		OLED_put_elipse(oled, 80, 32, 25, 20, OLED_FILL | OLED_WHITE | OLED_BORDER_WHITE);
		OLED_put_elipse(oled, 80, 32, 20, 15, OLED_FILL | OLED_BLACK | OLED_BORDER_WHITE);
		OLED_put_rectangle(oled, 40, 12, 80, 52, OLED_FILL | OLED_WHITE);
		OLED_put_elipse(oled, 65, 32, 5, 5, OLED_FILL | OLED_BLACK | OLED_BORDER_WHITE);
		OLED_put_rectangle(oled, 65, 30, 55, 34, OLED_FILL | OLED_BLACK);
	}
	
	OLED_refresh(oled);
	
	return OLED_EOK;
}


OLED_err OLED_draw_open_lock(OLED *oled)
{
	OLED_WITH_SPINLOCK(oled) {
		// Clear the display
		OLED_put_rectangle(oled, 0, 0, 127, 63, OLED_FILL | 1);
			
		// O letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 5, 30, 15, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 13, 8, 27, 12, OLED_FILL | OLED_BLACK);

		// P letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 20, 30, 30, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 10, 25, 18, 30, OLED_FILL | OLED_BLACK);
		OLED_put_rectangle(oled, 23, 23, 28, 28, OLED_FILL | OLED_BLACK);

		// E letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 35, 30, 45, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 12, 38, 19, 45, OLED_FILL | OLED_BLACK);
		OLED_put_rectangle(oled, 22, 38, 28, 45, OLED_FILL | OLED_BLACK);

		// N letter drawn with rectangles
		OLED_put_rectangle(oled, 10, 50, 30, 53, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 28, 53, 24, 55, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 25, 55, 16, 57, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 17, 57, 12, 60, OLED_FILL | OLED_WHITE);
		OLED_put_rectangle(oled, 10, 60, 30, 63, OLED_FILL | OLED_WHITE);

 		// draw the image of lock
 		OLED_put_elipse(oled, 80, 42, 20, 15, OLED_FILL | OLED_WHITE | OLED_BORDER_WHITE);
		OLED_put_elipse(oled, 80, 42, 14, 9, OLED_FILL | OLED_BLACK | OLED_BORDER_WHITE);
		OLED_put_rectangle(oled, 80, 22, 60, 62, OLED_FILL | OLED_BLACK);
 		OLED_put_rectangle(oled, 50, 4, 80, 34, OLED_FILL | OLED_WHITE);
 		OLED_put_elipse(oled, 68, 19, 5, 5, OLED_FILL | OLED_BLACK | OLED_BORDER_WHITE);
 		OLED_put_rectangle(oled, 68, 17, 60, 21, OLED_FILL | OLED_BLACK);
	}
	
	OLED_refresh(oled);
	
	return OLED_EOK;
}


OLED_err OLED_draw_alarm_lock(OLED *oled)
{
	// Clear the display
	OLED_put_rectangle(oled, 0, 0, 127, 63, OLED_FILL | 1);
	
	OLED_put_triangle (oled, 10, 5, 120, 30, 10, 62, 2);
	OLED_put_triangle (oled, 15, 15, 100, 30, 15, 52, 1 | OLED_FILL);
	OLED_put_rectangle(oled, 60, 28, 35, 35, OLED_FILL | OLED_WHITE);
	OLED_put_elipse(oled, 25, 32, 5, 5, OLED_FILL | OLED_WHITE | OLED_BORDER_WHITE);
	
	OLED_refresh(oled);
}
