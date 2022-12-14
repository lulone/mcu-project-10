/*
 * button.h
 *
 *  Created on: Nov 5, 2022
 *      Author: datjet7410
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

void get_key_input();
int is_button_pressed(int i);
int is_button_long_pressed(int i);
void reset_button_value(int i);

#endif /* INC_BUTTON_H_ */
