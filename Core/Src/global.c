/*
 * global.c
 *
 *  Created on: Dec 8, 2022
 *      Author: datjet7410
 */

#include "global.h"

int status = 0;
int red_road = 0;

int button_counter = 0;
int timing_counter_green = 0;
int timing_counter_yellow = 0;
int counter_on_7seg = 0;

int is_sleeped = 0;

int button_status[] = {BUTTON_RELEASED};
