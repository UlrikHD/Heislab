#include "state.h"
#include "hardware.h"
#include <stdlib.h>


State state_setDirection(int destinationFloor, Elevator* p_elev){
	int lastFloor = p_elev->g_floor;
	if (destinationFloor != lastFloor) {
		if (destinationFloor < lastFloor){
			state_setState(MOVING_DOWN);
		}
		else if (destinationFloor > lastFloor){
			state_setState(MOVING_UP);
		}
	}


	else if (floor == lastFloor){
		int above = p_elev->g_above;

		if (above) {
			state_setState(MOVING_DOWN);
		}
		else if (!above) {
			state_setState(MOVING_UP);
		}
	}
}

void state_startTimer(Elevator* p_elev){
	p_elev->g_timer = clock();
}

int state_timerDone(int seconds, Elevator* p_elev){
	clock_t currentTime = clock();
	clock_t prevTime = p_elev->g_timer;
	double timeElapsed = difftime(currentTime, prevTime);
	
	if (timeElapsed < seconds){
		p_elev->g_timerDone = 0;
		return 0;
	}
	else {
		p_elev->g_timerDone = 1;
		return 1;
	}
}


int state_atFloor() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS - 1; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
}

int state_checkStopButton(Elevator* p_elev) {
	if (hardware_read_stop_signal()) {
		p_elev->g_state = STOP;
		state_stateSwitch(p_elev);
	}
}


void state_stateSwitch(Elevator* p_elev){
	switch (p_elev->state){
		case IDLE: {
			printf("idle\n");
			hardware_command_door_open(0);
			state_checkStopButton(p_elev);
			break;
		}
		case MOVING_UP: {
			hardware_command_door_open(0);
			hardware_command_movement(HARDWARE_MOVEMENT_UP);
			p_elev->g_atFloor = 0;
			p_elev->g_above = 1;
			p_elev->g_direction = 1;
			printf("moving up\n");
			break;
		}
		case MOVING_DOWN: {
			hardware_command_door_open(0);
			state_checkStopButton(p_elev);
			hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
			p_elev->g_atFloor = 0;
			p_elev->g_above = 0;
			p_elev->g_direction = 0;
			printf("moving down\n");
			break;
		}
		case AT_FLOOR: {
			printf("at floor\n");
			p_elev->g_floor = state_atFloor();
			state_checkStopButton(p_elev);
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_floor_indicator_on(p_elev->g_floor);
			hardware_command_door_open(1);
			state_startTimer(p_elev->g_timer);
			p_elev->g_atFloor = 1;
			break;
		}
		case STOP: {
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_stop_light(1);
			if(p_elev->g_atFloor){
				hardware_command_door_open(1);
			}
			state_startTimer();
			//flush orders
			//dont take order?
			//restart main

			break;
		}
		default: { //necessary?
			p_elev->state = STOP;
			state_stateSwitch(p_elev);
		}
	}
}
