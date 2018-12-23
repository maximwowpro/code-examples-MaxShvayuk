#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

/* This library provides HAL to 28BYJ-48 (or other stepper engine with 4 control pins */

/* stepper
 *
 * !!! Notice that all control pins of stepper motor should be connected to the same PORTx.
 * PORT - pointer to PORTx register, where all pins of stepper are connected.
 * 
 * pin_1, pin_2, pin_3, pin_4 - numbers of pins of PORT where stepper is connected.
 */
typedef struct stepper_st
{
	volatile uint8_t *PORT;	/* addr of GPIO PORTx data register */
	
	uint8_t pin_1;
	uint8_t pin_2;
	uint8_t pin_3;
	uint8_t pin_4;
} stepper;

/* stepper_init - initialize stepper */
void stepper_init (stepper *motor, volatile uint8_t *DDR, volatile uint8_t *PORT, 
		   uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);


void stepper_clockwise (stepper *motor, uint8_t num_turns);


void stepper_counterclockwise (stepper *motor, uint8_t num_turns);


#endif	
