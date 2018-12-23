#include "led_rgb.h"

#include <avr/io.h>
#include <avr/interrupt.h>


void led_RGB_init(led_RGB *led, volatile uint8_t *PORT, volatile uint8_t *DDR,
		  uint8_t pin_red, uint8_t pin_green, uint8_t pin_blue)
{
	led->red   = 0;
	led->green = 0;
	led->blue  = 0;
	
	led->pin_red   = pin_red;
	led->pin_green = pin_green;
	led->pin_blue  = pin_blue;
	
	led->PORT = PORT;
	led->DDR  = DDR;
	
	/* configure LED pins as OUTPUTs */
	*(led->DDR ) |=  (1 << pin_red) |  (1 << pin_green) |  (1 << pin_blue); 
	/* set logic zero to LED pins    */
	*(led->PORT) &= ~(1 << pin_red) | ~(1 << pin_green) | ~(1 << pin_blue);
}


void led_RGB_red(led_RGB *led)
{
	led->red   = 0xFF;
	led->green = 0x00;
	led->blue  = 0x00;
	
	*(led->PORT) |=  (1 << led->pin_red);
	*(led->PORT) &= ~(1 << led->pin_green) & ~(1 << led->pin_blue);
}


void led_RGB_green(led_RGB *led)
{
	led->red   = 0x00;
	led->green = 0xFF;
	led->blue  = 0x00;
	
	*(led->PORT) |=  (1 << led->pin_green);
	*(led->PORT) &= ~(1 << led->pin_red) & ~(1 << led->pin_blue);
}


void led_RGB_blue(led_RGB *led)
{
	led->red   = 0x00;
	led->green = 0x00;
	led->blue  = 0xFF;
	
	*(led->PORT) |=  (1 << led->pin_blue);
	*(led->PORT) &= ~(1 << led->pin_red) & ~(1 << led->pin_green);
}


/* //TODO This implementation of led_RGB_blink is very quick and bad, it should be refactored */
void led_RGB_blink (led_RGB *led, uint8_t color)
{
	/* Invert the red pin logic level */
	*(led->PORT) ^= (1 << led->pin_red);
	*(led->PORT) &= ~(1 << led->pin_green) & ~(1 << led->pin_blue);
}
