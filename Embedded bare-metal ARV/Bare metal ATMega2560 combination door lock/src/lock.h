#ifndef LOCK__H
#define LOCK__H


#include "config.h"
#include "led_rgb.h"
#include "tools.h"
#include "motor.h"
#include "oled.h"

#include <stdbool.h>
#include <stdint.h>


/* 
 * This is the main file, where all other project's files are combined.
 * It provides simple to understand front - end to all features, 
 * avaiable in my lock.
 * //TODO: add 1-Wire, RFID using RC522
 */


/*
 * struct __lock_st__ - a struct which unites all modules of lock
 * 
 * In this struct I use several flags to manage the behavior of all modules of lock.
 * 
 * flag_state - the main flag. It may have 4 states:
 * 		0 - "wait", in this state the lock is closed, and the lock_sensors_interrogation() and
 * 		     lock_routine() functions are called in a loop. 
 * 		     Flags states: flag_oled    - 0	- lock
 * 				   flag_motor   - 2     - wait
 *    				   flag_rgb_led - 2	- blue
 * 		1 - "lock", to cause this state you should enter invallid password or key. 
 *                   Is almost the same as "wait" state, but RGB led lights red.
 * 		     Time: 3 seconds.
 * 		     Flags states: flag_oled    - 0	- lock
 * 				   flag_motor   - wait  - close
 *    				   flag_rgb_led - 0	- red
 * 		2 - "unlock", to cause this state you should enter valid password or key.
 * 		     Time: 5 seconds.
 * 		     Flags states: flag_oled    - 1	- unlock
 * 				   flag_motor   - 0     - open
 *    				   flag_rgb_led - 1	- green
 * 		3 - "break"(alarm), this state is causing when flag_state wasn't "unlock" and 
 * 		     INT0 interrupt happened. At pin with INT0 interrupt I have a reed switch. 
 * 		     Near it you should fix a magnet. If the door with magnet opens, the reed switch 
 * 		     breaks electrical circuit, the voltage at INT0 pin switches from VCC to GND 
 * 		     and the INT0 interrupt occurs.
 * 		     Time: until the valid password or key will not be entered.
 * 		     Flags states: flag_oled    - 2	- break
 * 				   flag_motor   - wait  - close
 *    				   flag_rgb_led - 3	- alarm
 * 		     
 * flag_oled - flag for display. It may have 3 states:
 * 		0 - "lock"  , displays closed lock;
 * 		1 - "unlock", displays opened lock;
 * 		2 - "break" , displays alarm notification if the lock was broken.
 * 
 * flag_motor - flag for stepper motor. It may have 3 states:
 * 		0  - is open;
 * 		1  - is close;
 * 		2  - wait (no moves).
 * 
 * flag_rgb_led - flag for RGB_LED. It may have 4 states:
 * 		0 - red;
 * 		1 - green;
 * 		2 - blue;
 * 		3 - alarm (the red diode is blinking).
 * 
 * flag_is_break - flag which indicates that the door was broken. It may have 2 states:
 * 		false - everything OK, door wasn't broken.
 * 		true  - break, alarm, the door was broken!!!
 * 
 * time_counter - this variable is using for time - management of lock.
 * 
 * num_keys - number of avaiable user's keys in EEPROM
 * 
 * key[9] - here readed keys and passwords will be placed for further processing.
 * 
 * keyboard_adc_pin - number of pin with ADC, where resistic keyboard is connected.
 * 
 * alarm_int_pin - INT interrupt pin where reed switch is connected.
 * 
 * motor - variable for vorking with stepper motor (28BYJ-48 or etc).
 * 
 * onewire_pin - to this pin 1-Wire data pin is connected.
 * 
 * oled - variable for working with OLED display managed by ssd1306 chip.
 * 
 * Also in alarm.c and alarm.h files there are functions which enable zummer alarm.
 * This alarm is avaiable ONLY by TIMER0 and zummer should be connected to PG5 pin.
 */
typedef struct __lock_st__ {
	volatile uint8_t flag_state;
	
	uint8_t flag_oled;
	uint8_t flag_motor;
	uint8_t flag_rgb_led;
	bool    flag_is_break;
	
	uint16_t time_counter;
	uint8_t  num_keys;
	
	uint8_t key[KEY_LENGHT];
	
	uint8_t keyboard_adc_pin;
	struct pin_in alarm_int_pin;
	uint8_t onewire_pin;
	led_RGB led;
	stepper motor;
	OLED oled;
} lock_st;


/* lock_init - itinialize lock.
 * 
 * analog_pin - pin number, where resistic keyboard is conected
 */
void lock_init (lock_st *lock, uint8_t analog_pin);


/* lock_sensors_interrogation - interrogates all sensors and processes this data.
 * 
 * Interrogates all sensors: keyboard, 1-Wire, RFID and UART. 
 * If entered by any of this channels key is VALID  , set flag_state at lock to 2 - "unlock".
 * If entered by any of this channels key is INVALID, set flag_state at lock to 1 - "lock".
 * If user haven't started enter any key or password, set flag_state at lock to 0 - "wait".
 * 
 * You should run this function in a loop.
 * 
 * Return:
 * 	true  - if user entered any key (no matter valid or invalid);
 * 	false - if user haven't started enter any key or password.
 */
void lock_sensors_interrogation (lock_st *lock);


/* 
 * lock_routine_flags - processes flags according to flag_state in lock.
 * 
 * You should run if after lock_sensors_interrogation() function.
 */
void lock_routine_flags (lock_st *lock);


/* 
 * lock_routine_actions - do actions according to setted flags in lock.
 * 
 * You should run if after lock_routine_flags() function.
 */
void lock_routine_actions (lock_st *lock);

#endif
