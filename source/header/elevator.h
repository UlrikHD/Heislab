#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "state.h"

/**
* @brief Variable that decides number of floors
*/
int floorsNun = 4
/**
* @brief Variable that decides number of order buttons (up, down, requested floor)
*/
int buttnonNum




/**
* @brief Struct that contains all the variables of the elevator.
*/
typedef struct {
	int g_floor;
	int g_above;
	int g_direction;
	int g_atFloor;
	State g_state;
	clock_t g_timer;
	int g_timerDone;

	int orders[floorsNum][buttonNum]

} Elevator

#endif