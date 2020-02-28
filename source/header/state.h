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
#include "../driver/hardware.h"
#include "../driver/io.h"
#include "orders.h"
#include "elevator.h"



/**
* @brief States used in @c switch in @c main() to call corresponding hardware functions.
*/

/**
 * @brief Set new time for global var g_timer to start timer
 * @param p_elev @c Pointer to @c Elevator object
 */
void state_startTimer(Elevator* p_elev);

/**
 * @brief Checks if given amount of @c seconds have passed since timer start
 * @param seconds The amount of seconds to check whether have elapsed since previous timer was set.
 * @param p_prevTimer Pointer to global variable @p g_timer
 * @return @c 1 if timer is done, @c 0 otherwise
 */
bool state_timerDone(int seconds, Elevator* p_elev);

/**
* @brief At new state or desire to execute function based on state
* @param p_elev of type @c Elevator*. !!Decided to send pointer to have access to all global variables inside elevator struct
* @return Dependent on switch result
*/
void state_stateSwitch(Elevator* p_elev);

/**
* @brief Checks all floor sensors.
* @return floor Floor number (0 indexed) or -1 if not a floor
*/
int state_atFloor();

void state_findFloor(Elevator* elevator) 

#endif