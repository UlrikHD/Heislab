#include "../header/orders.h"

int order_getDirection(Elevator elevator) {
	if (elevator.direction == 1) {
		for (int i = elevator.currentFloor + 1; i < elevator.floorsNum; ++i) {
			for (int j = 0; j < elevator.buttonNum; ++j) {
				if (elevator.orders[i][j]) {
					return 1;
				}
			}
		}
		for (int i = elevator.currentFloor; i >= 0; --i) {
			for (int j = 0; j < elevator.buttonNum; ++j) {
				if (elevator.orders[i][j]) {
					return -1;
				}
			}
		}
	}

	else {
		for (int i = elevator.currentFloor - 1; i >= 0; --i) {
			for (int j = 0; j < elevator.buttonNum; ++j) {
				if (elevator.orders[i][j]) {
					return -1;
				}
			}
		}
		for (int i = elevator.currentFloor; i < elevator.floorsNum; ++i) {
			for (int j = 0; j < elevator.buttonNum; ++j) {
				if (elevator.orders[i][j]) {
					return 1;
				}
			}
		}
	}
	return elevator.direction;
}

bool orders_noOrders(Elevator elevator) {
	for (int i = 0; i < elevator.floorsNum) {
		for (int j = 0; j < elevator.buttonNum) {
			if (elevator.orders[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void orders_emptyOrders(Elevator elevator) {
	for (int i = 0; i < elevator.floorsNum) {
		for (int j = 0; j < elevator.buttonNum) {
			elevator.orders[i][j] = false;
		}
	}
}

void getOrders(Elevator elevator) {
	for (int i = 0; i < elevator.floorNum; ++i) {
		elevator.orders[i][ORDER_UP] = hardware_read_order(i, HARDWARE_ORDER_UP);
		elevator.orders[i][ORDER_DOWN] = hardware_read_order(i, HARDWARE_ORDER_DOWN);
		elevator.orders[i][ORDER_INTERNAL] = hardware_read_order(i, HARDWARE_ORDER_INSIDE);
	}
}

bool orders_stopAtFloor(Elevator elevator) {
	if (elevator.direction == 1) {
		if (elevator.orders[elevator.currentFloor][ORDER_UP] || 
			elevator.orders[elevator.currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((order_getDirection(elevator) == -1) &&
				elevator.orders[elevator.currentFloor][ORDER_DOWN]) {
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					return true;
				}
	}
	else if (elevator.direction == -1) {
		if (elevator.orders[elevator.currentFloor][ORDER_DOWN] || 
			elevator.orders[elevator.currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((order_getDirection(elevator) == 1) &&
				elevator.orders[elevator.currentFloor][ORDER_UP]) {
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					return true;
				}
	}
	return false;
}
