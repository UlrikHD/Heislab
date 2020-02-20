/**
* @file
* @brief Defines the state machine of the elevator
* 
* Aksel Næstby
*/
#include <stdlib.h>
#include <stdbool.h>
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

State g_state = IDLE;
int g_lastFloor;
bool g_direction;
bool g_atFloor;

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

/**
 * @brief Decides which direction to go based on desired floor destination parameter
 * @param floor Destination
 * @return bool Where 1 is upwards and 0 is downwards
 */
bool state_setDirection(int floor)
{
	int lastFloor = state_getLastFloor();
	if (floor != lastFloor) 
	{
		if (floor < lastFloor)
		{
			state_setState(MOVING_DOWN);
		}
		else if (floor > lastFloor)
		{
			state_setState(MOVING_UP);
		}
	}
	else if (floor = lastFloor)
	{
		bool lastDirection = state_getDirection();
		if (lastDirection) //up
		{
			state_setState(MOVING_DOWN);
		}
		else if (!lastDirection) //down
		{
			state_setState(MOVING_UP);
		}
	}
}

#endif