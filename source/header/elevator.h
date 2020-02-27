#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "state.h"

/**
* @brief Variable that decides number of floors
*/
//int floorsNum = HARDWARE_NUMBER_OF_FLOORS
/**
* @brief Variable that decides number of order buttons (up, down, requested floor)
*/
//int buttnonNum = 3




/**
* @brief Struct that contains all the variables of the elevator.
*/
typedef struct {

    int currentFloor;
    int previousFloor;
    int direction;
    int buttnonNum = 3;
    int floorsNum = HARDWARE_NUMBER_OF_FLOORS;
	clock_t timer;
	int timerDone;
	int obstruction
    State state;
    

    bool orders[floorsNum][buttonNum]


} Elevator

#endif