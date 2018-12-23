#include "alarm.h"
#include "tools.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>


/* ZUMMER_TONE - determines the tone of zummer alarm squeak */
#define ZUMMER_TONE (80)


/* 
 * true  - the door is open
 * false - the door is close
 */
volatile bool flag_door_is_open = false;


/* 
 * Door open/close event handler. 
 * This interrupt occurs in ANY change of logic level at INT2 pin. 
 */
ISR(INT2_vect, ISR_NOBLOCK)
{
	if (PIND & (1 << 2))	/* if HIGH logic level (if door is close) */
		flag_door_is_open = false;
	else			/* if LOW  logic level (if door is open)  */
		flag_door_is_open = true;
}


void alarm_init_int2 (struct pin_in *int_pin)
{
	cli(); 				    /* Disable global interrupts */
	
	if (true == pin_in_read (int_pin))
		flag_door_is_open = false;  /* door is close 	  */
	else
		flag_door_is_open = true;   /* door is open  	  */
	
	pin_in_init (int_pin, 2, &DDRD, &PORTD, &PIND, false);
	
	EICRA |= (1 << ISC20); /* Any edge of INTn generates asynchronously an interrupt request */
	EIMSK |= (1 << INT2);  /* Enable INT2 interrupt 					 */
	
	sei(); 			    	    /* Enable global interrupts */
}


/* this ISR need for zummer alarm */
ISR(TIMER0_COMPB_vect, ISR_BLOCK)
{
	TCNT0 = 0;
}


void alarm_init_timer0_zummer (void)
{
	DDRG   |= (1 << PG5);		/* Set zummer pin as OUTPUT 	     */
	OCR0B   =  ZUMMER_TONE;		/* Compare register B 		     */
	TCCR0A |= (1 << COM0B0);	/* Change OC0B(PG5) logic level when counter value coinciding with OCR0B */
}


void alarm_timer0_zummer_on (void)
{
	/* TIMER0 ON. Prescaler = CLK/256 */
	TCCR0B |= (1 << CS02);
	/* Enable TIMER0 interrupts 	  */
	TIMSK0 |= (1 << OCIE0B);
}


void alarm_timer0_zummer_off (void)
{
	/* Timer0 OFF */
	TCCR0B &= ~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00);
	/* Disable TIMER0 interrupts 	  */
	TIMSK0 &= ~(1 << OCIE0B);
}
