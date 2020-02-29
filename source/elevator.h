/**
 * @file
 * @brief Library for elevator setup and basic functions connected to the elevator
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "hardware.h"
#include "driver/io.h"
#include "driver/channels.h"

#define BUTTON_NUM 3


/**
* @brief Enum for the different states the elevator can be in.
*/
typedef enum State{
    IDLE, /*!< State for when the elevator sits with no orders to service.  */
    MOVING, /*!< State for when the elevator is on the move */
	AT_FLOOR, /*!< State for when the elevator has reached a floor and services an order. */
	EMERGENCY_STOP /*!< State for when the stop button has been pressed */
} State;

/**
* @brief Struct that contains all the variables of the elevator.
*/
typedef struct Elevator {

    int currentFloor; /*!< Variable keeping tabs on last registered floor of elevator */
    int nextFloor; /*!< Variable showing next floor the elevator will pass */
    int direction; /*!< Keeping note on which way the elevator is going, 1 for up and -1 for down */
    int buttonNum; /*!< Variable telling how many sort of order buttons there are */
    int floorsNum; /*!< Variable telling how many floors the elevator got */
	clock_t timer; /*!< Variable for storing time when elevator door opens */
    double doorOpenTime; /*!< Variable deciding how long the elevator door should stay open, given in microseconds */
    bool obstruction; /*!< Variable keeping tabs on whether or not the door is obstructed */
    State state; /*!< Variable storing the state of the elevator */
    bool orders[HARDWARE_NUMBER_OF_FLOORS][BUTTON_NUM]; /*!< 2-dimensional list storing every order. 
    *For second index, 0 = order up, 1 = order down and 2 = order inside elevator */


} Elevator;

/**
 * @brief Checks if the elevator door is obstructed. 
 * If obstructed, resets the elevator timer.
 *
 * @param[in] p_elevator    Elevator to be checked for obstruction
 *
 * @return @c true if door is open and obstructed, @c false otherwise.
 */
bool elevator_doorObstructed(Elevator* p_elevator);

/**
 * @brief Initialise the elevator variable.
 * 
 * @param[out] p_elevator    Elevator to be initialised.
 */
void elevator_initElevator(Elevator* p_elevator);

/**
 * @brief Checks if the elevator is at a floor, and which floor.
 *
 * @return -1 if not at a floor, otherwise it will return the floor 
 * @p p_elevator is at, lowest floor starting at value 0.
 */
int elevator_atFloor();

/**
 * @brief Updates @c Elevator.currentFloor and @c Elevator.nextFloor.
 * 
 * @param[in, out] p_elevator    Elevator to have its floors updated.
 */
void elevator_updateFloors(Elevator* p_elevator);

#endif