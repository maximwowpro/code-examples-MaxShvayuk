#ifndef LED_RGB_H
#define LED_RGB_H

#include <avr/io.h>

#define RGB_COLOR_RED   (1)
#define RGB_COLOR_GREEN (2)
#define RGB_COLOR_BLUE  (3)

/* 
 * This library provides Hardware Abstraction Level to RGB LED.
 * //TODO: implement setting any color using PWM.
 */

/* led_RGB - HAL to RGB LED
 * 
 * !!! red, green, blue variables can be used just in PWM mode.
 * They determine the finally corour of LED.
 * red   - intencity of red   light (0 - 255)
 * green - intencity of green light (0 - 255)
 * blue  - intencity of blue  light (0 - 255)
 * 
 * !!! to take a less memory by the struct, 
 * I added to struct just one PORTx and DDRx registers.
 * So, all pins of RGB LED should be situated at the same PORT.
 * pin_red   - number of pin where red   LED is situated
 * pin_green - number of pin where green LED is situated
 * pin_blue  - number of pin where blue  LED is situated
 * 
 * 
 * PORT - pointer to PORTx register where RGB LED is situated
 * DDR  - pointer to DDRx  register where RGB LED is situated
 */
typedef struct __led_RGB {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	
	uint8_t pin_red;
	uint8_t pin_green;
	uint8_t pin_blue;
	
	volatile uint8_t *PORT;
	volatile uint8_t *DDR;
} led_RGB;


/* led_RGB_init - initialize RGB LED */
void led_RGB_init(led_RGB *led, volatile uint8_t *PORT, volatile uint8_t *DDR,
		  uint8_t pin_red, uint8_t pin_green, uint8_t pin_blue);


/* led_RGB_set - set the final colour of RGB LED.
 * 
 * This function you need just ib PWM mode.
 */
void led_RGB_set(led_RGB *led, uint8_t red, uint8_t green, uint8_t blue);


/* led_RGB_red - set red colour     */
void led_RGB_red(led_RGB *led);


/* led_RGB_green - set green colour */
void led_RGB_green(led_RGB *led);


/* led_RGB_blue - set blue colour   */
void led_RGB_blue(led_RGB *led);


/* 
 *led_RGB_blink - blinks with a one of colours 
 * 
 * color - can be RGB_COLOR_RED  RGB_COLOR_GREEN  RGB_COLOR_BLUE
 */
void led_RGB_blink (led_RGB *led, uint8_t color);


#endif
