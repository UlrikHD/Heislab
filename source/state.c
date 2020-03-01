/**
 * @file
 * @brief Implementation file for state library
 */
#include "state.h"


void state_updateTimer(Elevator* p_elevator) {
	p_elevator->timer = clock();
}

bool state_timerDone(const Elevator* p_elevator) {
	if (clock() - p_elevator->timer < p_elevator->doorOpenTime){
		return false;
	}
	else {
		return true;
	}
}

void state_findFloor(const Elevator* p_elevator) {
	if (elevator_atFloor() == -1) {
		if (p_elevator->currentFloor < p_elevator->nextFloor) {
			hardware_command_movement(HARDWARE_MOVEMENT_UP);
		}
		else {
			hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		}
	}
	else {
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	}
}

void state_stateSwitch(Elevator* p_elevator) {
	switch (p_elevator->state){
		case IDLE: //egentlig unødvendig
			//printf("Idle\n");
			break;
		case MOVING:
			p_elevator->direction = orders_getDirection(p_elevator);
			if (orders_getDirection(p_elevator) == 1) {
				hardware_command_movement(HARDWARE_MOVEMENT_UP);
				//printf("Moving up\n");
			}
			else {
				hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
				//printf("Moving down\n");
			}
			
			break;
		case AT_FLOOR:
			//printf("At floor\n");
			p_elevator->currentFloor = elevator_atFloor();
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_floor_indicator_on(p_elevator->currentFloor);
			hardware_command_door_open(1);
			orders_orderDone(p_elevator);
			state_updateTimer(p_elevator);
			break;
		case EMERGENCY_STOP:
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_stop_light(1);
			if(elevator_atFloor() != -1){
				hardware_command_door_open(1);
				state_updateTimer(p_elevator);
			}
			orders_emptyOrders(p_elevator);
			break;
		default: { 
			p_elevator->state = IDLE;
			break;
		}
	}
}

void state_checkStop(Elevator* p_elevator) {
	if (orders_activatedStopButton()) {
		p_elevator->state = EMERGENCY_STOP;
		state_stateSwitch(p_elevator);
	}
}

void state_getOrdersInStop(Elevator* p_elevator) {
	if (!orders_noOrders(p_elevator)) {
		if (p_elevator->currentFloor < p_elevator->nextFloor) {
			p_elevator->direction = 1;
		}
		else {
			p_elevator->direction = -1;
		}
		p_elevator->state = MOVING;
		state_stateSwitch(p_elevator);
	}
}

void state_continueMovement(Elevator* p_elevator) {
	p_elevator->direction = orders_getDirection(p_elevator);
	if (orders_getDirection(p_elevator) == 1) {
		hardware_command_movement(HARDWARE_MOVEMENT_UP);
	}
	else {
		hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
	}
}