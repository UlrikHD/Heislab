#include "elevator.h"

bool elevator_doorObstructed(Elevator* elevator) {
	if ((hardware_read_obstruction_signal() == 1) && io_read_bit(LIGHT_DOOR_OPEN)) {
		return true;
	}
	else {
		return false;
	}
}