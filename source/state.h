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





void state_updateTimer(Elevator* p_elevator);

bool state_timerDone(Elevator* p_elevator);

void state_stateSwitch(Elevator* p_elevator);

int elevator_atFloor();

void state_findFloor(Elevator* p_elevator); 

#endif