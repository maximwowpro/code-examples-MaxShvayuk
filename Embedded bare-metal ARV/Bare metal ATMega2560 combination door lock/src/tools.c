#include "tools.h"
#include "config.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <stdint.h>

extern void soft_delay(volatile uint16_t N);


ISR(TIMER2_OVF_vect, ISR_BLOCK)
{
	TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); /* stop timer */
	/* It's often required to manually reset interrupt flag */
        /* to avoid infinite processing of it.                  */
        /* not on AVRs (unless OCB bit set)                     */
        /* 	TIFR2 &= ~TOV2;                                 */
}

void sleep_ms(uint16_t ms_val)
{
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	cli();		/* Disable interrupts -- as memory barrier */
	sleep_enable();	/* Set SE (sleep enable bit) */
	sei();  	/* Enable interrupts. We want to wake up, don't we? */
	TIMSK2 |= (1 << TOIE2); /* Enable Timer2 Overflow interrupt by mask */
	while (ms_val--) {
		/* Count 1 ms from TCNT2 to 0xFF (up direction) */
		TCNT2 = (uint8_t)(0xFF - (F_CPU / 128) / 1000);

		/* Enable Timer2 */
		TCCR2B =  (1 << CS22) | (1 << CS20); /* f = Fclk_io / 128, start timer */

		sleep_cpu();	/* Put MCU to sleep */

		/* This is executed after wakeup */

	}
	sleep_disable();	/* Disable sleeps for safety */		
}


void pin_out_init (struct pin_out *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT)
{
	*DDR |= (1 << pin_num); 	/* set pin as OUTPUT */
	pin->PORT = PORT;
	pin->pin_num = pin_num;
}


void pin_in_init (struct pin_in *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT, 
		  volatile uint8_t *PIN, bool is_inbuilt_pull_up)
{
	*DDR &= ~(1 << pin_num); 	 /* set pin as INPUT 		     */
	if (true == is_inbuilt_pull_up)
		*PORT |= (1 << pin_num); /* connect inbuilt pull-up resistor */
		
	pin->pin_num = pin_num;
	pin->PIN = PIN;
}


void pin_in_out_init (struct pin_in_out *pin, uint8_t pin_num, volatile uint8_t *DDR, volatile uint8_t *PORT, 
		      volatile uint8_t *PIN, bool is_in, bool is_inbuilt_pull_up)
{
	if (true == is_in) {			 /* configure as INPUT 		     */
		*DDR &= ~(1 << pin_num);	 /* set pin as INPUT		     */
		if (true == is_inbuilt_pull_up)
			*PORT |= (1 << pin_num); /* connect inbuilt pull-up resistor */
	}
	else {					 /* configure as OUTPUT		     */
		*DDR |= (1 << pin_num); 	 /* set pin as OUTPUT		     */
	}
	
	pin->is_in = is_in;
	pin->pin_num = pin_num;
	pin->DDR  = DDR;
	pin->PORT = PORT;
	pin->PIN  = PIN;
}


void pin_out_set(struct pin_out *pin, bool value)
{
	if (true == value)
		*(pin->PORT) |=  (1 << pin->pin_num);
	else
		*(pin->PORT) &= ~(1 << pin->pin_num);
}


bool pin_in_read (struct pin_in *pin)
{
	uint8_t val = *(pin->PIN);
	if ((1 << pin->pin_num) & val)	/* if HIGH */
		return true;
	else				/* if LOW  */
		return false;
}


void pin_in_out_set (struct pin_in_out *pin, bool value)
{
	if (true == pin->is_in) {
		*(pin->DDR) |= (1 << pin->pin_num);	/* set as OUTPUT */
		pin->is_in = false;
	}
	
	if (true == value)
		*(pin->PORT) |=  (1 << pin->pin_num);
	else 
		*(pin->PORT) &= ~(1 << pin->pin_num);
}


bool pin_in_out_read (struct pin_in_out *pin)
{
	if (false == pin->is_in) {
		*(pin->DDR) &= ~(1 << pin->pin_num);	/* set as INPUT */
		pin->is_in = true;
	}
	
	uint8_t val = *(pin->PIN);
	if ((1 << pin->pin_num) & val)	/* if HIGH */
		return true;
	else				/* if LOW  */
		return false;
}

