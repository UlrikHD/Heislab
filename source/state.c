#include "state.h"


void state_startTimer(Elevator* p_elev) {
	p_elev->timer = clock();
}

bool state_timerDone(Elevator* elevator) {
	if (clock() - elevator->timer < elevator->doorOpenTime){
		return false;
	}
	else {
		return true;
	}
}


int state_atFloor() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
}


void state_findFloor(Elevator* elevator) {
	if (state_atFloor() == -1) {
		if (elevator->currentFloor < elevator->nextFloor) {
			hardware_command_movement(HARDWARE_MOVEMENT_UP);
		}
		else {
			hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		}
		elevator->state = MOVING;
	}
}



void state_stateSwitch(Elevator* p_elev) {
	switch (p_elev->state){
		case IDLE: {
			printf("Idle\n");
			hardware_command_door_open(0);
			break;
		}
		case MOVING: {
			hardware_command_door_open(0);
			state_checkStopButton(p_elev);
			if (order_getDirection(p_elev) == 1) {
				hardware_command_movement(HARDWARE_MOVEMENT_UP);
				p_elev->nextFloor += p_elev->currentFloor;
				printf("Moving up\n");
			}
			else {
				hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
				p_elev->nextFloor -= p_elev->currentFloor;
				printf("Moving down\n");
			}
			
			break;
		}
		case AT_FLOOR: {
			printf("At floor\n");
			p_elev->currentFloor = state_atFloor();
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_floor_indicator_on(p_elev->currentFloor);
			hardware_command_door_open(1);
			orders_orderDone(p_elev);
			state_startTimer(p_elev);
			break;
		}
		case EMERGENCY_STOP: {
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_stop_light(1);
			if(state_atFloor != -1){
				hardware_command_door_open(1);
			}
			orders_emptyOrders(p_elev);
			break;
		}
		default: { //necessary?
			p_elev->g_state = STOP;
			state_stateSwitch(p_elev);
		}
	}
}
