#include "motor.h"
#include "tools.h"

#include <avr/io.h>

#include <stdint.h>

/* value of NUM_SWITCHING_IN_ONE_TURN depends of concrete model of stepper */
#define NUM_SWITCHING_IN_ONE_TURN (525)

#define STEPPER_DELAY (20)


void stepper_init (stepper *motor, volatile uint8_t *DDR, volatile uint8_t *PORT, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
{
	/* set pins as OUTPUTs */
	*DDR |= (1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4);
	
	motor->pin_1 = pin1;
	motor->pin_2 = pin2;
	motor->pin_3 = pin3;
	motor->pin_4 = pin4;
	motor->PORT  = PORT;
}


void stepper_clockwise (stepper *motor, uint8_t num_turns)
{
	for (uint16_t i = 0; i < num_turns * NUM_SWITCHING_IN_ONE_TURN; i++) {
		*(motor->PORT) |=  (1 << motor->pin_1) |  (1 << motor->pin_4);
		*(motor->PORT) &= ~(1 << motor->pin_2) & ~(1 << motor->pin_3);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_3) |  (1 << motor->pin_4);
		*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_2);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_2) |  (1 << motor->pin_3);
		*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_4);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_1) |  (1 << motor->pin_2);
		*(motor->PORT) &= ~(1 << motor->pin_3) & ~(1 << motor->pin_4);
		soft_delay(STEPPER_DELAY);
	}
	
	/* set LOW logic level on all control pins */
	*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_2) & ~(1 << motor->pin_3) & ~(1 << motor->pin_4);
}


void stepper_counterclockwise (stepper *motor, uint8_t num_turns)
{
	for (uint16_t i = 0; i < num_turns * NUM_SWITCHING_IN_ONE_TURN; i++) {
		*(motor->PORT) |=  (1 << motor->pin_1) |  (1 << motor->pin_2);
		*(motor->PORT) &= ~(1 << motor->pin_3) & ~(1 << motor->pin_4);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_2) |  (1 << motor->pin_3);
		*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_4);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_3) |  (1 << motor->pin_4);
		*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_2);
		soft_delay(STEPPER_DELAY);
		
		*(motor->PORT) |=  (1 << motor->pin_1) |  (1 << motor->pin_4);
		*(motor->PORT) &= ~(1 << motor->pin_2) & ~(1 << motor->pin_3);
		soft_delay(STEPPER_DELAY);
	}
	
	/* set LOW logic level on all control pins */
	*(motor->PORT) &= ~(1 << motor->pin_1) & ~(1 << motor->pin_2) & ~(1 << motor->pin_3) & ~(1 << motor->pin_4);
}

