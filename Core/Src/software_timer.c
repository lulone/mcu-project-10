/*
 * software_timer.c
 *
 *  Created on: Oct 24, 2022
 *      Author: datjet7410
 */

#include "software_timer.h"

void set_timer(int* flag, int* counter, int duration){
	*flag = 0;
	*counter = duration / TIMER_CYCLE;
}

void timer_run(int* flag, int* counter){
	if(*counter > 0){
		*counter -= 1;
		if(*counter <= 0) *flag = 1;
	}
}
void clear_timer(int* flag, int* counter){
	*flag = 0;
	*counter = 0;
}

/*
 * timer for traffic LEDs
 */
int timer_traffic_flag = 0;
int timer_traffic_counter = 0;

void set_timer_traffic(int duration){
	set_timer(&timer_traffic_flag, &timer_traffic_counter, duration);
}
void timer_traffic_run(){
	timer_run(&timer_traffic_flag, &timer_traffic_counter);
}
void clear_timer_traffic(){
	clear_timer(&timer_traffic_flag, &timer_traffic_counter);
}

/*
 * timer for UART display
 */
int timer_display_flag = 0;
int timer_display_counter = 0;

void set_timer_display(int duration){
	set_timer(&timer_display_flag, &timer_display_counter, duration);
}
void timer_display_run(){
	timer_run(&timer_display_flag, &timer_display_counter);
}

/*
 * timer for button count long press
 */
int timer_button_flag = 0;
int timer_button_counter = 0;

void set_timer_button(int duration){
	set_timer(&timer_button_flag, &timer_button_counter, duration);
}
void timer_button_run(){
	timer_run(&timer_button_flag, &timer_button_counter);
}
void clear_timer_button(){
	clear_timer(&timer_button_flag, &timer_button_counter);
}

/*
 * timer for pedestrian light
 */
int timer_ped_flag = 0;
int timer_ped_counter = 0;

void set_timer_pedestrian(int duration){
	set_timer(&timer_ped_flag, &timer_ped_counter, duration);
}
void timer_pedestrian_run(){
	timer_run(&timer_ped_flag, &timer_ped_counter);
}
void clear_timer_pedestrian(){
	clear_timer(&timer_ped_flag, &timer_ped_counter);
}

/*
 * ISR
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	get_key_input();
	timer_traffic_run();
	timer_display_run();
	timer_button_run();
	timer_pedestrian_run();
}
