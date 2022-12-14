/*
 * fsm_manual.c
 *
 *  Created on: Oct 24, 2022
 *      Author: datjet7410
 */

#include "fsm_manual.h"

void button_processing_manual(){
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

	switch (button_status[1]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(1)){

				status = MAN_RED_GREEN;

				button_status[1] = BUTTON_PRESSED;
				clear_timer_button();
			}

			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(1)){
				button_status[1] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(1)){
				status = AUTO_INIT;
				set_timer_traffic(DURATION_INIT);
			}
			break;
		default:
			break;
	}

	switch (button_status[2]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(2)){

				status++;
				if (status > MAN_GREEN_RED)	status = MAN_RED_GREEN;

				button_status[2] = BUTTON_PRESSED;
				clear_timer_button();
			}

			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(2)){
				button_status[2] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(2)){
				// do nothing
			}
			break;
		default:
			break;
	}

	switch (button_status[3]) {
		case BUTTON_RELEASED:
			if(is_button_pressed(3)){

				status--;
				if (status < MAN_RED_GREEN)	status = MAN_GREEN_RED;

				button_status[3] = BUTTON_PRESSED;
				clear_timer_button();
			}

			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(3)){
				button_status[3] = BUTTON_RELEASED;
				set_timer_button(DURATION_BUTTON_SLEEP);
			}

			if(is_button_long_pressed(3)){
				// do nothing
			}
			break;
		default:
			break;
	}
}

/* fsm for manual modes */
void fsm_manual_run(){
	switch (status) {
		case MAN_INIT:
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
				status = MAN_RED_GREEN;
				clear_timer_traffic();
			}
			break;

		case MAN_RED_GREEN:
			set_traffic(TRAFFIC_ROAD_0, TRAFFIC_COLOR_RED);
			set_traffic(TRAFFIC_ROAD_1, TRAFFIC_COLOR_GREEN);

			button_processing_manual();
			break;

		case MAN_YELLOW_YELLOW:
			set_traffic(TRAFFIC_ROAD_0, TRAFFIC_COLOR_YELLOW);
			set_traffic(TRAFFIC_ROAD_1, TRAFFIC_COLOR_YELLOW);

			button_processing_manual();

			break;
		case MAN_GREEN_RED:
			set_traffic(TRAFFIC_ROAD_0, TRAFFIC_COLOR_GREEN);
			set_traffic(TRAFFIC_ROAD_1, TRAFFIC_COLOR_RED);

			button_processing_manual();
			break;

		default:
			break;
	}
}
