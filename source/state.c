#include "state.h"
#include "hardware.h"
#include <stdlib.h>


State g_state = IDLE;
State state_getState() {
	return g_state;
}

void state_setState(State state) {
	g_state = state;
	return;
}

int state_getLastFloor(){
	return g_lastFloor;
}

int state_getDirection(){
	return g_direction;
}

int state_getAtFloor(){
	return g_atFloor;
}

void state_setDirection(int floor){
	int lastFloor = state_getLastFloor();
	if (floor != lastFloor) {
		if (floor < lastFloor){
			state_setState(MOVING_DOWN);
			//state_stateSwitch();
		}
		else if (floor > lastFloor){
			state_setState(MOVING_UP);
			//state_stateSwitch();
		}
	}
	else if (floor == lastFloor){
		bool lastDirection = state_getDirection();
		if (lastDirection) {//up
			state_setState(MOVING_DOWN);
			//state_stateSwitch();
		}
		else if (!lastDirection) {//down
			state_setState(MOVING_UP);
			//state_stateSwitch();
		}
	}
}

void state_startTimer(){
	g_timer = clock();
}

int state_timerDone(int seconds){
	clock_t currentTime = clock();
	double timeElapsed = difftime(currentTime, g_timer);
	
	if (timeElapsed < seconds){
		return 0;
	}
	else if (timeElapsed >= seconds){
		return 1; //timer done
	}
	return 0;
}

void state_setAtFloor(int value){
	if(value == 1 || value == 0){
		g_atFloor = value;
	}
	return;
}

void state_setLastFloor(int floor){
	if(0 < floor || floor < 5){
		g_lastFloor = floor;
	}
	return;
}


void state_stateSwitch(){
		
	switch (state_getState()){
		case IDLE: {
			printf("idle\n");
			hardware_command_door_open(0);
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			break;
		}
		case MOVING_UP: {
			state_setAtFloor(0);
			printf("moving up\n");
			hardware_command_door_open(0);
			hardware_command_movement(HARDWARE_MOVEMENT_UP);
			break;
		}
		case MOVING_DOWN: {
			state_setAtFloor(0);
			printf("moving down\n");
			hardware_command_door_open(0);
			hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
			break;
		}
		case AT_FLOOR: {
			printf("at floor\n");
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			int sensorRead = 0;
			for (int i = 1; i<5;i++){
				if(hardware_read_floor_sensor(i))
				{
					sensorRead = 1;
					state_setAtFloor(1);
					state_setLastFloor(i);
					break;
				}
				else if (i == 4) //sensor doesnt register
				{
					state_setState(IDLE);
					sensorRead = 0;
				}
			}
			if(sensorRead == 0){break;}
			int currentFloor = state_getLastFloor();
			hardware_command_floor_indicator_on(currentFloor);
			hardware_command_door_open(1);
			state_startTimer(3);
			//empty orders who have destination here:
			//order_removeOrder(this_order);
			break;
		}
		default:
		case STOP: {
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			hardware_command_stop_light(1);
			if(state_getAtFloor()){
				hardware_command_door_open(1);
			}
			state_startTimer();
			//flush orders
			//dont take orders?

			break;
		}
	}
}
