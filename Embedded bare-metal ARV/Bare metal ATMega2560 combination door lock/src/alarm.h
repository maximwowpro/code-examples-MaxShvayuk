#include "tools.h"

#include <stdbool.h>

/*
 * I use external INT2 interrupt to notice that door was opened.
 * In ATMEGA2560 INT2 pin is PD2 pin.
 * If you want change the alarm pin - you should rewrite all alarm functions.
 * 
 * The door opening sensor consists of a reed switch and a magnet.
 */


/* 
 * true  - the door is open
 * false - the door is close
 */
extern volatile bool flag_door_is_open;


/* alarm_init_int2 - initialize door opening sensor at INT2 pin */
void alarm_init_int2(struct pin_in *int_pin);


/* alarm_init_timer0_zummer - initialize zummer alarm
 * 
 * I am using TIMER0 pin B to make a zummer's signal.
 * If your MCU is NOT ATMega2560 - you should change pin, which uses in this function.
 */
void alarm_init_timer0_zummer (void);


/* alarm_timer0_zummer_on - turn ON zummer at TIMER0 pin B */
void alarm_timer0_zummer_on (void);


/* alarm_timer0_zummer_on - turn OFF zummer at TIMER0 pin B */
void alarm_timer0_zummer_off (void);







