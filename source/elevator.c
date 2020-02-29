#include "elevator.h"

bool elevator_doorObstructed(Elevator* p_elevator) {
	if ((hardware_read_obstruction_signal() == 1) && io_read_bit(LIGHT_DOOR_OPEN)) {
		p_elevator->timer = clock();
		//printf("reset");
		return true;
	}
	else {
		return false;
	}
}

void elevator_initElevator(Elevator* p_elevator) {
		p_elevator->currentFloor = 0;
		p_elevator->nextFloor = 1;
		p_elevator->direction = 1;
		p_elevator->buttonNum = BUTTON_NUM;
		p_elevator->floorsNum = HARDWARE_NUMBER_OF_FLOORS;
		p_elevator->timer = clock();
		p_elevator->doorOpenTime = 3000000; //in microseconds
		p_elevator->obstruction = false;
		p_elevator->state = IDLE;
		for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i) {
			for (int j = 0; j < BUTTON_NUM; ++j) {
				p_elevator->orders[i][j] = false;
			}
		}
}