/**
 * @file
 * @brief Library of functions related to the state of the elevator.
 */
#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
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
 * the @c EMERGENCY_STOP -case will constantly be looped over by main().
 * This is desireable behaviour, but it also means you shouldn't add functionality
 * inside the case that you only want to run once when the state transition happen.
 */
void state_stateSwitch(Elevator* p_elevator);

/**
 * @brief Function that switches state to @c EMERGENCY_STOP if the stop button is pressed.
 * 
 * If the stop button is pressed, the function will call on @c state_stateSwitch()
 * 
 * @param[in, out] p_elevator    Elevator to check for stop request.
 */
void state_checkStop(Elevator* p_elevator);

/**
 * @brief Function that handles requests while the elevator is in @c EMERGENCY_STOP state.
 * 
 * @param[in, out] p_elevator    Elevator in @c EMERGENCY_STOP to have its requests handled.
 * 
 * @warning This function will check if Elevator got any orders and with its own 
 * internal logic decide which direction to go. @c orders_getDirection() should not be
 * used in tandem (in @c EMERGENCY_STOP state) with this function as 
 * @c orders_getDirection() is not designed to handle an Elevator that has 
 * stopped between two floors.
 * 
 * @warning The function will switch Elevator.state to @c MOVING and call on 
 * @c state_stateSwitch() if it finds any orders
 */
void state_getOrdersInStop(Elevator* p_elevator);

/**
 * @brief Simple function only meant for increasing the readability of the code, 
 * makes sure the elevator keeps moving in the right direction
 * 
 * @param[in, out] p_elevator    Elevator in @c EMERGENCY_STOP to have its requests handled.
 * 
 * @warning This function will check if Elevator got any orders and with its own 
 * internal logic decide which direction to go. @c orders_getDirection() should not be
 * used in tandem (in @c EMERGENCY_STOP state) with this function as 
 * @c orders_getDirection() is not designed to handle an Elevator that has 
 * stopped between two floors.
 * 
 * @warning The function will switch Elevator.state to @c MOVING and call on 
 * @c state_stateSwitch() if it finds any orders
 */
void state_continueMovement(Elevator* p_elevator);

#endif