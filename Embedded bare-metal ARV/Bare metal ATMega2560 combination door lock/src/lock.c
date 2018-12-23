#include "lock.h"
#include "config.h"
#include "led_rgb.h"
#include "tools.h"
#include "motor.h"
#include "uart.h"
#include "keyboard.h"
#include "eeprom.h"
#include "oled.h"
#include "alarm.h"

#include <stdbool.h>
#include <stdint.h>


#define HOW_MANY_TIMES_INTERROGATE_SENSORS (10)


void lock_init (lock_st *lock, uint8_t analog_pin)
{
	lock->flag_state    = 0;	/* wait 	 */
	lock->flag_oled     = 0;	/* lock 	 */
	lock->flag_motor    = 1;	/* close 	 */
	lock->flag_rgb_led  = 2;	/* blue 	 */
	lock->flag_is_break = false;	/* door wasn't broken */
	
	lock->time_counter  = 0;
	lock->num_keys = _eeprom_read_byte (0x00); /* read a number of avaiable keys from EEPROM adress 0x00 */
	
	lock->keyboard_adc_pin = analog_pin;
	adc_init (analog_pin);		/* initialize ADC */
	
	for (uint8_t i = 0; i < KEY_LENGHT; i++)
		lock->key[i] = 0;
}


void lock_sensors_interrogation (lock_st *lock)
{
	uint8_t error_code = 0;
	bool is_valid = false;
	
	for (uint8_t i = 0; i < HOW_MANY_TIMES_INTERROGATE_SENSORS; i++) {
		error_code = keyboard_read_password(lock->key);
		if (4 == error_code) {
			uart_print_str ("\nKeyboard: you entered CANCEL button\n");
			continue;
		} else if (3 == error_code) {
			uart_print_str ("\nKeyboard: can't allocate memory for key array\n");
			continue;
		} else if (2 == error_code) {
			uart_print_str ("\nKeyboard: you pushed invalid button\n");
			continue;
		} else if (0 == error_code) {
			is_valid = is_user_key_valid (lock->num_keys, lock->key);
			if (false == is_valid) {
				uart_print_str ("\nKeyboard: you entered invalid password\n");
				if (false == lock->flag_is_break)
					lock->flag_state = 1; /* lock */
				else			      /* if door was broken   */
					lock->flag_state = 3; /* set alarm mode       */
				break;
			} else if (true == is_valid) {
				uart_print_str ("\nKeyboard: you entered valid password, unlock...\n");
				lock->flag_state = 2; 	      /* unlock */
				lock->flag_is_break = false;
				break;
			}
		}
		
		uart_read_command(lock);
	}
	
	/* check was the door broken */
	if (true == flag_door_is_open) {
		if (2 == lock->flag_state)	/* if lock was unlocked */
			return;
		else {
			lock->flag_state = 3;   /* set alarm mode       */
			lock->flag_is_break = true;
		}
	}	
}


/* //TODO: refactor this function for more optimal flags management */
void lock_routine_flags (lock_st *lock)
{
	alarm_timer0_zummer_off();		/* OFF alarm zummer */
	
	switch (lock->flag_state) {
		case 0:		/* wait   */
			lock->flag_oled    = 0; /* lock */
			lock->flag_motor   = 2; /* wait */
			lock->flag_rgb_led = 2; /* blue */
			break;
		case 1:		/* lock   */
			lock->flag_oled    = 0; /* lock */
			lock->flag_motor   = 2; /* wait */
			lock->flag_rgb_led = 0; /* red  */
			break;
		case 2:		/* unlock */
			lock->flag_oled    = 1; /* unlock */
			lock->flag_motor   = 0; /* open   */
			lock->flag_rgb_led = 1; /* green  */
			break;
		case 3: 	/* alarm  */
			lock->flag_oled    = 2; /* break  */
			lock->flag_motor   = 2; /* wait   */
			lock->flag_rgb_led = 3; /* alarm  */
			alarm_timer0_zummer_on(); /* ON alarm zummer */
			break;
		default:
			lock->flag_state   = 0; /* wait */
			lock->flag_oled    = 0; /* lock */
			lock->flag_motor   = 2; /* wait */
			lock->flag_rgb_led = 2; /* blue */
			break;
	}
}


/* //TODO: refactor this function for more optimal flags handling */
void lock_routine_actions (lock_st *lock)
{
	switch (lock->flag_oled) {
		case 0:
			OLED_draw_closed_lock (&(lock->oled));
			break;
		case 1:
			OLED_draw_open_lock   (&(lock->oled));
			break;
		case 2:
			OLED_draw_alarm_lock  (&(lock->oled));
			break;
		default:
			OLED_draw_closed_lock (&(lock->oled));
			break;
	}
	
	switch (lock->flag_rgb_led) {
		case 0:
			led_RGB_red   (&(lock->led));
			break;
		case 1:
			led_RGB_green (&(lock->led));
			break;
		case 2:
			led_RGB_blue  (&(lock->led));
			break;
		case 3:
			led_RGB_blink (&(lock->led), RGB_COLOR_RED);
			break;
	}
	
	switch (lock->flag_motor) {
		case 0:		/* open  */
			stepper_clockwise (&(lock->motor), NUM_TURNS_FOR_STEPPER);
			break;
		case 1:		/* close */
			break;
		case 2:		/* wait  */
			break;
		default:
			break;
	}
	
	switch (lock->flag_state) {
		case 0:		/* wait   */
			break;
		case 1:		/* lock   */
			soft_delay (3000);
			break;
		case 2:		/* unlock */
			soft_delay (5000);
			while (true == flag_door_is_open){}	/* wait untill door is closed */
			stepper_counterclockwise (&(lock->motor), NUM_TURNS_FOR_STEPPER);
			break;
		case 3:
			return;
	}
	
	lock->flag_state = 0;   /* set wait state */
}

