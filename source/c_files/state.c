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

void state_startTimer(clock_t* p_time){
	*p_newTimeStamp = clock();
}

int state_timerDone(int seconds, clock_t* prevTimer){
	clock_t currentTime = clock();
	double timeElapsed = difftime(currentTime, *prevTimer);
	
	if (timeElapsed < seconds){
		return 0;
	}
	else if (timeElapsed >= seconds){
		return 1; //timer done
	}
	return 0;
}


int state_atFloor() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS - 1; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
}


void state_stateSwitch(Elevator* p_elev){
		
	switch (p_elev->state){
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
