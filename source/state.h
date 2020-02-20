/**
* @file
* @brief Defines the state machine of the elevator
* 
* Aksel Næstby
*/

#ifndef STATE_H
#define STATE_H

State g_state = IDLE;
int g_lastFloor;
bool g_direction;
bool g_atFloor

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
State state_getState();


/**
* @brief Set global state
* @param[in] state State of elevator
*/
void state_setState(State state);

/**
* @brief Get last floor
* @return @c int
*/
int state_getLastFloor();

/**
* @brief Get direction
* @return @c bool
*/
bool state_getDirection();

/**
* @brief Get atFloor
* @return @c bool
*/
bool state_getAtFloor();


#endif