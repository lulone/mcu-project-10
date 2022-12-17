/*
 * software_timer.h
 *
 *  Created on: Oct 24, 2022
 *      Author: datjet7410
 */

#ifndef SRC_SOFTWARE_TIMER_H_
#define SRC_SOFTWARE_TIMER_H_

#include "global.h"
#include "button.h"

/*
 * timer for traffic LEDs
 */
extern int timer_traffic_flag;
extern int timer_traffic_counter;
void set_timer_traffic(int duration);
void clear_timer_traffic();
/*
 * timer for UART display
 */
extern int timer_display_flag;
void set_timer_display(int duration);

/*
 * timer for button long press count
 */
extern int timer_button_flag;
void set_timer_button(int duration);
void clear_timer_button();

/*
 * timer for pedestrian light
 */
extern int timer_ped_flag;
void set_timer_pedestrian(int duration);
void clear_timer_pedestrian();
/*
 * ISR
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* SRC_SOFTWARE_TIMER_H_ */
