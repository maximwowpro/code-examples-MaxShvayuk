#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

/* This file contains functions for working with resistic keyboard.
 * 
 * The electrical scheme and PCB layout of this keyboard you can find in github repo.
 * My version of keyboard has 15 buttons: 13 analog and 2 digital.
 * You can use this buttons in such way:
 * 	1	2	3
 * 	4	5	6
 * 	7	8	9
 * 	0      but1   CANCEL
 *     NOT     INT0    INT1
 * but1 you can program at your discretion.
 * CANCEL button I am using for cancel password entering.
 * NOT button I don't recomend to use because using of it can be a 
 * reason of many bugs (due to resistors ratings I am using in my keyboard).
 * If you take resistors with other ratings in order to have at NOT button 
 * voltage which is less than VCC at least 0.5 Volt - you can use this button too.
 * 
 * INT0 and INT1 button can be connected to digital pins (including external interrupts pins).
 * The pull-up resistors are built-in keyboard.
 * 
 * You may don't worry about button's bouncing because my keyboard has built-in capacitors, 
 * which remove all contact's bouncing.
 */

typedef enum {
	/* BUT_0 - BUT_12 - numbers of pushed button */
	BUT_0 = 0,
	BUT_1,
	BUT_2,
	BUT_3,
	BUT_4,
	BUT_5,
	BUT_6,
	BUT_7,
	BUT_8,
	BUT_9,
	BUT_10,
	BUT_11_CANCEL,   /* CANCEL entering password button 			  	*/
	BUT_12_NOT_USE,  /* This button has very much false presses, so DON'T USE IT!!! */
	BUT_VCC, 	 /* if any button wasn't pushed 				*/
	BUT_ERR  	 /* if ADC returned value that doesn't match any button 	*/
} k_button; /* means "keyboard_button */


/* adc_init - configure ADC */
void adc_init(uint8_t analog_pin);


inline void adc_start_converting()
{
	/* If at the moment conversion doesn't happen - starts it. If conversion is in process - do nothing */
	ADCSRA |= (1 << ADSC);
}


/* keyboard_read_num - read a number, entered by user at resistic keyboard and returns it.
 * 
 * Run adc_start_converting() 10 times, after this there is an average ADC converting value
 * at adc_result variable (watch keyboard.c). Then converst 0-255 adc_result value to 
 * 0 1 2 3 4 5 6 7 8 9 10 11 12, where 0 - 9 are numbers buttons in keyboard and 
 * 10 11 12 are additional buttons. 
 * 
 * Return:
 *  BUT_0 - BUT_12 - number of pushed button if OK;
 *  BUT_VCC - if Vadc == VCC (if any button wasn't pushed)
 *  BUT_ERR - if adc_result contains invalid result.
 */
k_button keyboard_read_num();


/* keyboard_read_password - read 8 - numbers password from keyboard and write it to *pass.
 * 
 * Note that user can enter just numbers 0-9, otherwise return error code "2".
 * 
 * Return:
 *  0  - everything OK
 *  1  - user didn't start enter password
 *  2  - user entered invalid number
 *  3  - can't allocate memory for *pass
 *  4  - user pushed CANCEL entering password button
 */
uint8_t keyboard_read_password(uint8_t *pass);

