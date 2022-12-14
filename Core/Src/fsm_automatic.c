/*
 * fsm_automatic.c
 *
 *  Created on: Oct 24, 2022
 *      Author: datjet7410
 */

#include "fsm_automatic.h"

void button_processing_automatic(){
	switch (button_status[1]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(1)){

				// do nothing

				button_status[1] = BUTTON_PRESSED;
				clear_timer_button();
			}

			if(timer_button_flag == 1){

			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(1)){
				button_status[1] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(1)){
				// do nothing
			}
			break;
		default:
			break;
	}

	switch (button_status[2]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(2)){

				// do nothing

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
				status = TIMING_INIT;
				set_timer_traffic(DURATION_INIT);
			}
			break;
		default:
			break;
	}

	switch (button_status[3]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(3)){

				// do nothing

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
				status = MAN_INIT;
				set_timer_traffic(DURATION_INIT);
			}
			break;
		default:
			break;
	}
}

void fsm_automatic_run(){

	switch (status) {
		case AUTO_INIT:
			red_road = TRAFFIC_ROAD_0;
			button_counter = 0;
			counter_on_7seg = 0;

			for(int i = 1; i < NUM_BUTTONS; i++){
				button_status[i] = BUTTON_RELEASED;
			}

			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_RED);

			if(timer_traffic_flag == 1){
				status = AUTO_RED_GREEN;
				set_timer_traffic(timing_counter_green);
			}
			break;

		case AUTO_RED_GREEN:
			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_GREEN);

			/*
			 * Road 0 display 7seg
			 */
			if(red_road == TRAFFIC_ROAD_0){
				counter_on_7seg = (timer_traffic_counter * TIMER_CYCLE + timing_counter_yellow  ) / 1000;
			}else{
				counter_on_7seg = timer_traffic_counter * TIMER_CYCLE / 1000;
			}

			button_processing_automatic();

			if(timer_traffic_flag == 1){
				status = AUTO_RED_YELLOW;
				set_timer_traffic(timing_counter_yellow);
			}

			break;

		case AUTO_RED_YELLOW:
			set_traffic(red_road, TRAFFIC_COLOR_RED);
			set_traffic(!red_road, TRAFFIC_COLOR_YELLOW);

			/*
			 * Road 0 display 7seg
			 */
			counter_on_7seg = timer_traffic_counter * TIMER_CYCLE / 1000;


			button_processing_automatic();

			if(timer_traffic_flag == 1){
				status = AUTO_RED_GREEN;
				set_timer_traffic(timing_counter_green);

				/*
				 *
				 */
				switch_red_road();
			}
			break;

		default:
			break;
	}
}
