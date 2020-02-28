#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <time.h>
#include <stdbool.h>
#include "../driver/hardware.h"
#include "../driver/io.h"
#include "../driver/channels.h"

#define BUTTON_NUM 3

typedef enum State{
    IDLE,
    MOVING,
	AT_FLOOR,
	EMERGENCY_STOP
} State;


/**
* @brief Struct that contains all the variables of the elevator.
*/
typedef struct Elevator {

    int currentFloor;
    int nextFloor;
    int direction;
    int buttonNum;
    int floorsNum;
	clock_t timer;
    double doorOpenTime; //in microseconds
    bool obstruction;
    State state;
    bool orders[HARDWARE_NUMBER_OF_FLOORS][BUTTON_NUM];


} Elevator;

bool elevator_doorObstructed(Elevator* elevator);

#endif