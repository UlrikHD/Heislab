#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <time.h>
#include <stdbool.h>

typedef enum State{
    IDLE,
    MOVING,
	AT_FLOOR,
	STOP
} State;



/**
* @brief Variable that decides number of floors
*/
//int floorsNum = HARDWARE_NUMBER_OF_FLOORS
/**
* @brief Variable that decides number of order buttons (up, down, requested floor)
*/
//int buttnonNum = 3


/**
* @brief Struct that contains all the variables of the elevator.
*/
typedef struct {

    int currentFloor;
    int nextFloor;
    int direction;
    int buttnonNum = 3;
    int floorsNum = HARDWARE_NUMBER_OF_FLOORS;
	clock_t timer;
    double doorOpenTime = 6000000 //in microseconds
    bool obstruction false;
    State state = IDLE;
    bool orders[floorsNum][buttonNum]


} Elevator;

bool elevator_doorObstructed(Elevator* elevator);

#endif