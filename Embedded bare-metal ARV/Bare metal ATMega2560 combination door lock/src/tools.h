#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdint.h>
#include <stdbool.h>

/* This file contains some useful things which uses in project */

/* soft_delay - simple software delay */
inline void soft_delay(volatile uint16_t N)
{
	volatile uint8_t inner = 0xFF;
	while (N--) {
		while (inner--);
	}
	return;
}


/* sleep_ms - sleep on specified amount of miliseconds using TIMER2 */
void sleep_ms(uint16_t ms_val); //TODO: fix this func on ATMega2560


/* struct pin_out - HAL for OUTPUT pins */
struct pin_out
{
	volatile uint8_t *PORT;
	
	uint8_t pin_num;
};


/* struct pin_in - HAL for INPUT pins */
struct pin_in
{
	volatile uint8_t *PIN;
	
	uint8_t pin_num;
};


/* struct pin_in_out - HAL for pins which can be both INPUT and OUTPUT */
struct pin_in_out
{
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	volatile uint8_t *PIN;
	
	bool is_in;
	
	uint8_t pin_num;
};


void pin_out_init (struct pin_out *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT);


void pin_in_init (struct pin_in *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT, 
		  volatile uint8_t *PIN, bool is_inbuilt_pull_up);


void pin_in_out_init (struct pin_in_out *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT, 
		      volatile uint8_t *PIN, bool is_in, bool is_inbuilt_pull_up);


void pin_out_set(struct pin_out *pin, bool value);


bool pin_in_read (struct pin_in *pin);


void pin_in_out_set (struct pin_in_out *pin, bool value);


bool pin_in_out_read (struct pin_in_out *pin);

#endif
