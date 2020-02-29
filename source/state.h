/**
 * @file
 * @brief Library of functions related to the state of the elevator.
 */
#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stdio.h>
#include "hardware.h"
#include "driver/io.h"
#include "orders.h"
#include "elevator.h"


/**
 * @brief Simple function only meant for increasing the readability of the code, 
 * updates the elevator timer.
 *
 * @param[out] p_elevator    Elevator that will have its timer updated.
 */
void state_updateTimer(Elevator* p_elevator);

/**
 * @brief Function that checks if more time has passed than set 
 * by @c Elevator.doorOpenTime since @c Elevator.timer was updated.
 *
 * @param[in] p_elevator    Elevator to have its time checked.
 *
 * @return @c true if more than has passed than @c Elevator.doorOpenTime defines,
 * @c false if less time has passed.
 */
bool state_timerDone(Elevator* p_elevator);

/**
 * @brief Function used in @c IDLE state to find a floor if current location
 * is unkown. Should only be needed during the intialising phase.
 *
 * @param[in] p_elevator    Elevator to ensure got a defined state and position.
 */
void state_findFloor(Elevator* p_elevator); 

/**
 * @brief Primary function of state.h, takes care of all logic needed when
 * the elevator switches state.
 * 
 * The function is a single switch that contains all the necessary logic to care of
 * of a state switch of the elevator. The switch contains five cases:
 *      - @c IDLE - used only print out the state transition for easier monitoring of states.
 *      - @c MOVING - starts the motor.
 *      - @c AT_FLOOR - opens the door, starts the timer and removes completed order,
 *      - @c EMERGENCY_STOP - stops the motor, empties the queue and activates the stop light.
 *      - @c default - should in theory never be called upon.
 *
 * @param[in, out] p_elevator    Elevator to have its state transition handled.
 * 
 * @warning With the current setup in main.c, unlike every other case, 
 * the EMERGENCY_STOP-case will constantly be looped over by main().
 * This is desireable behaviour, but it also means you shouldn't add functionality
 * inside the case that you only want to run once when the state transition happen.
 */
void state_stateSwitch(Elevator* p_elevator);

#endif