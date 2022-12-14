/*
 * fsm_timing.c
 *
 *  Created on: Dec 10, 2022
 *      Author: datjet7410
 */

#include "fsm_timing.h"

void counter_up(int num){
	button_counter += num;
	if(button_counter > 99) button_counter = 1;
	counter_on_7seg = button_counter;
}

void counter_down(int num){
	button_counter -= num;
	if(button_counter < 1) button_counter = 99;
	counter_on_7seg = button_counter;
}

void button_processing_timing(){
	if(timer_button_flag == 1){
		if(is_sleeped){
			counter_on_7seg--;
			if(counter_on_7seg <= 0){
				is_sleeped = 0;
				clear_timer_button();

				status = AUTO_INIT;
				set_timer_traffic(DURATION_INIT);
			}
			set_timer_button(1000);
		}else{
			is_sleeped = 1;
			counter_on_7seg = DURATION_SLEEP_COUNT_DOWN / 1000;
			set_timer_button(1000);
		}
		return;
	}

	switch (button_status[2]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(2)){

				counter_up(1);

				button_status[2] = BUTTON_PRESSED;
				clear_timer_button();
			}

			if(timer_button_flag == 1){

			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(2)){
				button_status[2] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(2)){
				counter_up(10);
			}
			break;
		default:
			break;
	}

	switch (button_status[3]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(3)){

				counter_down(1);

				button_status[3] = BUTTON_PRESSED;
				clear_timer_button();
			}

			if(timer_button_flag == 1){

			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(3)){
				button_status[3] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(3)){
				counter_down(10);
			}
			break;
		default:
			break;
	}
}


void fsm_timing_run(){
	switch (status) {
		case TIMING_INIT:
			set_timer_button(DURATION_BUTTON_SLEEP);

			red_road = TRAFFIC_ROAD_0;
			button_counter = 0;
			counter_on_7seg = 0;

			for(int i = 1; i < NUM_BUTTONS; i++){
				button_status[i] = BUTTON_RELEASED;
			}

			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_RED);

			if(timer_traffic_flag == 1){
				status = TIMING_GREEN;
				set_timer_traffic(500);
			}
			break;

		case TIMING_GREEN:
			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_GREEN);

			button_processing_timing();

			if(is_button_pressed(1)){
				if(button_counter != 0){
					timing_counter_green = button_counter * 1000;

					button_counter = 0;
					counter_on_7seg = 0;
					set_timer_button(DURATION_BUTTON_SLEEP);

					status = TIMING_YELLOW;
					set_timer_traffic(500);
				}else{
					counter_on_7seg = button_counter;
					set_timer_button(DURATION_BUTTON_SLEEP);
				}
			}

			if(timer_traffic_flag == 1){
				switch_red_road();
				set_timer_traffic(500);
			}

			break;

		case TIMING_YELLOW:
			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_YELLOW);


			button_processing_timing();

			if(is_button_pressed(1)){
				if(button_counter != 0){
					timing_counter_yellow = button_counter * 1000;

					button_counter = 0;
					counter_on_7seg = 0;
					set_timer_button(DURATION_BUTTON_SLEEP);

					status = AUTO_INIT;
					set_timer_traffic(DURATION_INIT);
				}else{
					counter_on_7seg = button_counter;
					set_timer_button(DURATION_BUTTON_SLEEP);
				}
			}

			if(timer_traffic_flag == 1){
				switch_red_road();
				set_timer_traffic(500);
			}
			break;

		default:

			break;
	}
}
