/*
 * global.h
 *
 *  Created on: Dec 8, 2022
 *      Author: datjet7410
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

/*
 * fsm automatic and manual status
 */
extern int status;

/*
 * Automatic modes status
 */
#define AUTO_INIT 10
#define AUTO_RED_GREEN 11
#define AUTO_RED_YELLOW 12


#define DURATION_INIT 2000
/*
 * default duration
 */
#define DURATION_RED_GREEN 10000
#define DURATION_RED_YELLOW 3000

/*
 * Timing mode status
 */
#define TIMING_INIT 20
#define TIMING_GREEN 21
#define TIMING_YELLOW 22
extern int timing_counter_green;
extern int timing_counter_yellow;


/*
 * Manual modes status
 */
#define MAN_INIT 30
#define MAN_RED_GREEN 31
#define MAN_YELLOW_YELLOW 32
#define MAN_GREEN_RED 33

/*
 * fsm for button input processing
 */
#define NUM_BUTTONS 4
extern int button_status[NUM_BUTTONS];

#define BUTTON_RELEASED 0
#define BUTTON_PRESSED 1
#define BUTTON_SLEEP 2

extern int button_counter;
extern int counter_on_7seg;
#define DURATION_BUTTON_SLEEP 30000

extern int is_sleeped;
#define DURATION_SLEEP_COUNT_DOWN 5000

#define DURATION_LONG_PRESS 3000
#define DURATION_AFTER_FIRST_LONG_PRESS 1000

/*
 * Pedestrian light
 */
extern int is_ped;
extern int ped_road;

/*
 * Which road is RED during all automatic and manual modes
 * value : 0 or 1
 */
extern int red_road;

#define TIMER_CYCLE 10

#define DURATION_DISPLAY 100

#endif /* INC_GLOBAL_H_ */
