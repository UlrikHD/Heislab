/**
* @file
* @brief Defines the state machine of the elevator
* 
* Aksel Næstby
*/
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
int g_direction;
int g_atFloor;
clock_t g_timer;

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
* @return direction where 1 is up and 0 is down
*/
int state_getDirection();

/**
* @brief Get atFloor
* @return floor where @c 1 is up and @c 0 is down
*/
int state_getAtFloor();

/**
 * @brief Decides which direction to go based on desired floor destination parameter
 * @param floor Destination
 * @return direction Where 1 is upwards and 0 is downwards
 */
int state_setDirection(int floor);

/**
 * @brief Set global value @c g_atFloor 
 * @param floor @c 1 for true, @c 0 for false
 */
void state_setAtFloor(int value);


/**
 * @brief Set last floor
 * @param floor Int to indicate floor number
 */
void state_setLastFloor(int floor);

/**
 * @brief Start a countdown timer
 */
void state_startTimer();

/**
 * @brief Checks if given amount of @c seconds have passed since timer start
 * @param seconds 
 * @return @c 1 if timer is done, @c 0 otherwise
 */
int timerDone(int seconds);


#endif