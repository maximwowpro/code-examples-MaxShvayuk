#include "config.h"
#include "eeprom.h"
#include "uart.h"
#include "lock.h"
#include "keyboard.h"
#include "motor.h"
#include "oled.h"
#include "alarm.h"

#include <avr/io.h>

#include <stdbool.h>
#include <stdint.h>


int main (void)
{
	uart_init();
	uart_print_str("\nHello from avr lock!\n");

	lock_st lock;
	
	/* init lock (resistic keyboard analog pin is 0x00 pin */
	lock_init (&lock, 0x00);
	
	/* init stepper motor */
	stepper_init(&(lock.motor), &DDRB, &PORTB, 7, 6, 5, 4);
	
	/* init OLED */
	uint8_t fb[1024] = {0};
	OLED_init(&(lock.oled), 128, 64, fb, 200000, 0b0111100);
	
	/* init RGB LED */
	led_RGB_init ( &(lock.led), &PORTE, &DDRE, 4, 5, 3);
	
	/* init alarm reed switch pin */
	alarm_init_int2 ( &(lock.alarm_int_pin) );
	
	/* init alarm zummer */
	alarm_init_timer0_zummer();

	while (1)
	{
		lock_sensors_interrogation (&lock);
		lock_routine_flags  	   (&lock);
		lock_routine_actions 	   (&lock);
	}
}
