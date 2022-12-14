/*
 * traffic_led.h
 *
 *  Created on: Dec 6, 2022
 *      Author: datjet7410
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "global.h"
/*
 * road
 */
#define TRAFFIC_ROAD_0 0
#define TRAFFIC_ROAD_1 1

/*
 * color
 */
#define TRAFFIC_COLOR_OFF 0
#define TRAFFIC_COLOR_RED 1
#define TRAFFIC_COLOR_GREEN 2
#define TRAFFIC_COLOR_YELLOW 3

/*
 * set color for road
 */
void set_traffic(int road, int color);

/*
 * switch RED road
 */
void switch_red_road();

#endif /* INC_TRAFFIC_LIGHT_H_ */
