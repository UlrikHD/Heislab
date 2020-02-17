#include "state.h"

#include <stdlib.h>

State g_state = IDLE;

State state_getState() {
	return state;
}

void state_setState(State state) {
	g_state = state;
	return;
}
while (1) {

	switch (state) {
	case IDLE: {
		break;
	}
	case MOVING_UP: {
		hardware_command_movement(HardwareMovement HARDWARE_MOVEMENT_UP);
		break;
	}
	case MOVING_DOWN: {
		break;
	}
	case AT_FLOOR: {
		break;
	}
	case default:
	case STOP: {
		break;
	}
	}
}