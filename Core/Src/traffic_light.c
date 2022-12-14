/*
 * traffic_led.c
 *
 *  Created on: Dec 6, 2022
 *      Author: datjet7410
 */

#include "traffic_light.h"


void set_traffic(int road, int color){
	GPIO_TypeDef *led_A_port;
	uint16_t led_A_pin;

	GPIO_TypeDef *led_B_port;
	uint16_t led_B_pin;

	switch (road){
		case TRAFFIC_ROAD_0:
			led_A_port = D2_GPIO_Port;
			led_A_pin = D2_Pin;
			led_B_port = D3_GPIO_Port;
			led_B_pin = D3_Pin;
			break;
		case TRAFFIC_ROAD_1:
			led_A_port = D4_GPIO_Port;
			led_A_pin = D4_Pin;
			led_B_port = D5_GPIO_Port;
			led_B_pin = D5_Pin;
			break;
		default:
			break;
	}

	switch (color) {
		case TRAFFIC_COLOR_OFF:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, 0);
			HAL_GPIO_WritePin(led_B_port, led_B_pin, 0);
			break;
		case TRAFFIC_COLOR_RED:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, 1);
			HAL_GPIO_WritePin(led_B_port, led_B_pin, 0);
			break;
		case TRAFFIC_COLOR_GREEN:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, 0);
			HAL_GPIO_WritePin(led_B_port, led_B_pin, 1);
			break;
		case TRAFFIC_COLOR_YELLOW:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, 1);
			HAL_GPIO_WritePin(led_B_port, led_B_pin, 1);
			break;
		default:
			break;
	}
}

void switch_red_road(){
	red_road = !red_road;
}
