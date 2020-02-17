/**
* @file
* @brief Defines the state machine of the elevator
* 
* Aksel Næstby
*/

#ifndef STATE_H
#define STATE_H

/**
* @brief States used in @c switch in @c main() to call corresponding hardware functions.
*/
typedef enum{
	IDLE,
	MOVING_UP,
	MOVING_DOWN,
	AT_FLOOR,
	STOP
} State;

/**
* @brief Get global state
* @return @c State
*/
State state_getState()


/**
* @brief Set global state
* @param[in] state State of elevator
*/
void state_setState(State state);
#endif