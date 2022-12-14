/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: datjet7410
 */

#include "button.h"

GPIO_TypeDef* buttons_port[NUM_BUTTONS] = {A0_GPIO_Port, A1_GPIO_Port, A2_GPIO_Port, A3_GPIO_Port};
uint16_t buttons[NUM_BUTTONS] = {A0_Pin, A1_Pin, A2_Pin, A3_Pin};


#define IS_RELEASED GPIO_PIN_SET
#define IS_PRESSED GPIO_PIN_RESET

int button_long_pressed_flags[NUM_BUTTONS] = {0};

/*
 * Long press processing
 */
int button_values[NUM_BUTTONS] = {IS_RELEASED};
int timers_button_long_press[NUM_BUTTONS] = {DURATION_LONG_PRESS / TIMER_CYCLE};


/*
 * debounce 3 times
 */
int key_reg_0[NUM_BUTTONS] = {IS_RELEASED};
int key_reg_1[NUM_BUTTONS] = {IS_RELEASED};
int key_reg_2[NUM_BUTTONS] = {IS_RELEASED};

/* timer interrupt for button read */
void get_key_input(){
	for(int i = 0; i < NUM_BUTTONS; i++){
		key_reg_2[i] = key_reg_1[i];
		key_reg_1[i] = key_reg_0[i];
		key_reg_0[i] = HAL_GPIO_ReadPin(buttons_port[i], buttons[i]);

		if((key_reg_2[i] == key_reg_1[i]) && (key_reg_1[i] == key_reg_0[i])){
			if(button_values[i] != key_reg_2[i]){
				button_values[i] = key_reg_2[i];
				if(key_reg_2[i] == IS_PRESSED){
					timers_button_long_press[i] = DURATION_LONG_PRESS / TIMER_CYCLE;
				}
			}else{
				timers_button_long_press[i]--;
				if(timers_button_long_press[i] <= 0){
					if(key_reg_2[i] == IS_PRESSED){
						button_long_pressed_flags[i] = 1;
					}
					timers_button_long_press[i] = DURATION_AFTER_FIRST_LONG_PRESS / TIMER_CYCLE;
				}
			}
		}
	}
}

int is_button_long_pressed(int i){
	if(button_long_pressed_flags[i] == 1){
		button_long_pressed_flags[i] = 0;
		return 1;
	}
	return 0;
}

int is_button_pressed(int i){
	return button_values[i] == IS_PRESSED;
}

void reset_button_value(int i){
	button_values[i] = IS_RELEASED;
	button_long_pressed_flags[i] = 0;
}
