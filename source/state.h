/**
* @file
* @brief Defines the state machine of the elevator
* 
*/

#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "hardware.h"
#include "driver/io.h"
#include "orders.h"
#include "elevator.h"





void state_startTimer(Elevator* elevator);

bool state_timerDone(Elevator* elevator);

void state_stateSwitch(Elevator* elevator);

int state_atFloor();

//void state_findFloor(Elevator* elevator) 

#endif