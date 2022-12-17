/*
 * pedestrian_light.c
 *
 *  Created on: Dec 9, 2022
 *      Author: HUY
 */
#include "pedestrian_light.h"

void set_pedestrian_light(int road){
	GPIO_TypeDef *led_A_port = D6_GPIO_Port;
	uint16_t led_A_pin = D6_Pin;

	GPIO_TypeDef *led_B_port = D7_GPIO_Port;
	uint16_t led_B_pin = D7_Pin;
	switch (road){
		case TRAFFIC_ROAD_0:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, HAL_GPIO_ReadPin(D3_GPIO_Port, D3_Pin));
			HAL_GPIO_WritePin(led_B_port, led_B_pin, HAL_GPIO_ReadPin(D2_GPIO_Port, D2_Pin));
			if (HAL_GPIO_ReadPin(D3_GPIO_Port, D3_Pin) == HAL_GPIO_ReadPin(D2_GPIO_Port, D2_Pin))
			  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 100);
			else if (HAL_GPIO_ReadPin(D3_GPIO_Port, D3_Pin) < HAL_GPIO_ReadPin(D2_GPIO_Port, D2_Pin))
			  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1000);
			break;
		case TRAFFIC_ROAD_1:
			HAL_GPIO_WritePin(led_A_port, led_A_pin, HAL_GPIO_ReadPin(D5_GPIO_Port, D5_Pin));
			HAL_GPIO_WritePin(led_B_port, led_B_pin, HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin));
			if (HAL_GPIO_ReadPin(D5_GPIO_Port, D5_Pin) == HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin))
			  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1000);
			else if (HAL_GPIO_ReadPin(D5_GPIO_Port, D5_Pin) < HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin))
			  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1000);
			break;
		default:
			break;
	}
}

