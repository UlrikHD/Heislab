#pragma once
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
tyepdef struct {
    int floor;
    int direction;
    State status;
    

    int orders[floorsNum][buttonNum]

} Elevator