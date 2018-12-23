#include "keyboard.h"
#include "config.h"
#include "tools.h"
#include "uart.h"

#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

#include <stdint.h>
#include <stdlib.h>


/* ADC will make 10 conversions for greater accuracy */
#define adc_converts_max (10)

uint8_t adc_converts_counter = 0;

/* Stores ADC conversion data for each conversion */
uint16_t adc_result = 0;


ISR(ADC_vect, ISR_BLOCK)
{
	adc_result = ADCH;
	adc_converts_counter++;
}


void adc_init(uint8_t analog_pin)
{
	/* ADC power ON; enable ADC_vect interrupt; prescaler = CLK / 128 (0x07) */
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | 0x07;
	
	/* TODO: add assertion */
	if (analog_pin > 7)
		analog_pin = 0;
	
	/* Reference voltage is VCC; left-hand representation of result; input ADC channel is analog_pin */
	ADMUX |= (1 << REFS0) | (1 << ADLAR) | analog_pin;
}


extern void adc_start_converting();


k_button keyboard_read_num()
{
	adc_converts_counter = 0;
	/* Make several measurments to exclude false voltage values */
	while (adc_converts_counter <= adc_converts_max)
		adc_start_converting();
	
	if (adc_result > 17 && adc_result < 23)
		return BUT_1;
	else if (adc_result > 35 && adc_result < 41)
		return BUT_2;
	else if (adc_result > 50 && adc_result < 56)
		return BUT_3;
	else if (adc_result > 103 && adc_result < 109)
		return BUT_4;
	else if (adc_result > 86 && adc_result < 92)
		return BUT_5;
	else if (adc_result > 68 && adc_result < 74)
		return BUT_6;
	else if (adc_result > 123 && adc_result < 129)
		return BUT_7;
	else if (adc_result > 145 && adc_result < 151)
		return BUT_8;
	else if (adc_result > 166 && adc_result < 172)
		return BUT_9;
	else if (adc_result > 230 && adc_result < 236)
		return BUT_0;
	else if (adc_result > 207 && adc_result < 213)
		return BUT_10;
	else if (adc_result > 186 && adc_result < 192)
		return BUT_11_CANCEL;
	else if (adc_result > 248 && adc_result < 252)
		return BUT_12_NOT_USE;
	else if (adc_result > 251 && adc_result < 256) /* if Vadc == VCC */
		return BUT_VCC;
	else
		return BUT_ERR;
	
	return BUT_ERR; /* do this just to avoid gcc's warning */
}


uint8_t keyboard_read_password(uint8_t *pass)
{
	if (NULL == pass) {
		pass = malloc (KEY_LENGHT * sizeof(*pass));
		if (NULL == pass)
			return 3; /* can't allocate memory for *pass array */
	}
	
	soft_delay(1000);
	uint8_t pass_it = 1; /* password string iterator */
	k_button tmp = keyboard_read_num();
	/* user should enter: 1 @delay@ 2 @delay@ 3 @delay@ 4 @delay@ 5 @delay@ ...
	 * in @delay@ (when any button isn't pressed, keyboard_read_num() returns BUT_VCC (because this time Vadc == VCC).
	 * using this flag, I check that first button was released and I can read the value of the second button 
	 * false - @delay@ wasn't happened, can't read new button
	 * true  - @delay@ was happened, can read new button
	 */
	volatile bool pass_delay_flag = false;
	
	if (BUT_VCC == tmp || BUT_ERR == tmp)
		return 1; /* user didn't start enter password */
	else if (BUT_10 == tmp)
		return 2;
	else {
		pass[pass_it] = tmp;
		pass_it++;
		uart_print_uint8_dec(tmp);  
		uart_print_str("   ");
	}
	
	while (pass_it < KEY_LENGHT) {
		
		/* wait untill user releases button */
		while (!pass_delay_flag) {
			tmp = keyboard_read_num();
			if (BUT_VCC == tmp)
				pass_delay_flag = true;
		}
		
		/* wait untill user pushed any button */
		while (true) {
			soft_delay(150);
			tmp = keyboard_read_num();
			if (BUT_VCC != tmp && BUT_ERR != tmp)
				break;
		}
		
		if (BUT_11_CANCEL == tmp)	       	    /* user pushed CANCEL button  */
			return 4;
		
		if (BUT_12_NOT_USE == tmp || BUT_10 == tmp) /* user pushed invalid button */
			return 2;
		
		uart_print_uint8_dec(tmp);  
		uart_print_str("   ");
		
		pass[pass_it] = (uint8_t)tmp;
		pass_it++;
		pass_delay_flag = false;
	}
	uart_print_str("\n");

	return 0;
}

