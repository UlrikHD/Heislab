/**
 * @file
 * @brief Library of functions related to the state of the elevator.
 */
#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include "hardware.h"
#include "driver/io.h"
#include "orders.h"
#include "elevator.h"


/**
 * @brief Function used in @c IDLE state to find a floor if current location
 * is unkown. Should only be needed during the intialising phase.
 *
 * @param[in] p_elevator    Elevator to ensure got a defined state and position.
 */
void state_findFloor(const Elevator* p_elevator); 

/**
 * @brief Primary function of state.h, takes care of all logic needed when
 * the Elevator switches state.
 * 
 * The function is a single switch that contains all the necessary logic to take 
 * care of a state switch of the Elevator. The switch contains five cases:
 *      - @c IDLE - used more actively during debugging, is now only used to catch cases 
 * where @c state_stateSwitch() is called while Elevator is in IDLE.
 *      - @c MOVING - starts the motor.
 *      - @c AT_FLOOR - opens the door, starts the timer and removes completed order,
 *      - @c EMERGENCY_STOP - stops the motor, empties the queue and activates the stop light.
 *      - @c default - should in theory never be called upon, will set Elevator.state to @c IDLE
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
 * @brief Function that handles requests while the Elevator is in @c EMERGENCY_STOP state.
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
 * makes sure the Elevator keeps moving in the right direction.
 * 
 * @param[in, out] p_elevator    Elevator to continue its movement
 */
void state_continueMovement(Elevator* p_elevator);

#endif