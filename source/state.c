#include "state.h"
#include "hardware.h"
#include <stdlib.h>


State state_getState() 
{
	return g_state;
}

void state_setState(State state) 
{
	g_state = state;
	return;
}

int state_getLastFloor()
{
	return g_lastFloor;
}

bool state_getDirection()
{
	return g_direction;
}

bool state_getAtFloor()
{
	return g_atFloor;
}



state_stateSwitch()
{
		
	switch (state_getState())
	{
		case IDLE: 
		{
			break;
		}
		case MOVING_UP: 
		{
			hardware_command_movement(HARDWARE_MOVEMENT_UP);
			break;
		}
		case MOVING_DOWN: 
		{
			break;
		}
		case AT_FLOOR: 
		{
			break;
		}
		default:
		case STOP: 
		{
			break;
		}
	}
}