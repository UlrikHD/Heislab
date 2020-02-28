#include "elevator.h"

bool elevator_doorObstructed(Elevator* elevator) {
	if ((hardware_read_obstruction_signal() == 1) && io_read_bit(LIGHT_DOOR_OPEN)) {
		return true;
	}
	else {
		return false;
	}
}

void elevator_initElevator(Elevator elevator) {
		elevator.currentFloor = 0;
		elevator.nextFloor = 1;
		elevator.direction = 1;
		elevator.buttonNum = BUTTON_NUM;
		elevator.floorsNum = HARDWARE_NUMBER_OF_FLOORS;
		elevator.timer = clock();
		elevator.doorOpenTime = 6000000; //in microseconds
		elevator.obstruction = false;
		elevator.state = IDLE;
		for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i) {
			for (int j = 0; j < BUTTON_NUM; ++j) {
				elevator.orders[i][j] = false;
			}
		}
}