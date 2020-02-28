#include "orders.h"

void orders_lightOrders(Elevator* elevator) {
	for (int i = 0; i < elevator->floorsNum; ++i) {
		for (int j = HARDWARE_ORDER_UP; j <= HARDWARE_ORDER_DOWN; ++j) {
			hardware_command_order_light(i, j, elevator->orders[i][j]);
		}
	}
}

int orders_getDirection(Elevator* elevator) {
	if (elevator->direction == 1) {
		for (int i = elevator->currentFloor + 1; i < elevator->floorsNum; ++i) {
			for (int j = 0; j < elevator->buttonNum; ++j) {
				if (elevator->orders[i][j]) {
					return 1;
				}
			}
		}
		for (int i = elevator->currentFloor; i >= 0; --i) {
			for (int j = 0; j < elevator->buttonNum; ++j) {
				if (elevator->orders[i][j]) {
					return -1;
				}
			}
		}
	}

	else {
		for (int i = elevator->currentFloor - 1; i >= 0; --i) {
			for (int j = 0; j < elevator->buttonNum; ++j) {
				if (elevator->orders[i][j]) {
					return -1;
				}
			}
		}
		for (int i = elevator->currentFloor; i < elevator->floorsNum; ++i) {
			for (int j = 0; j < elevator->buttonNum; ++j) {
				if (elevator->orders[i][j]) {
					return 1;
				}
			}
		}
	}
	return elevator->direction;
}

bool orders_noOrders(Elevator* elevator) {
	for (int i = 0; i < elevator->floorsNum; ++i) {
		for (int j = 0; j < elevator->buttonNum; ++j) {
			if (elevator->orders[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void orders_emptyOrders(Elevator* elevator) {
	for (int i = 0; i < elevator->floorsNum; ++i) {
		for (int j = 0; j < elevator->buttonNum; ++j) {
			elevator->orders[i][j] = false;
		}
	}
}

void orders_getOrders(Elevator* elevator) {
	for (int i = 0; i < elevator->floorsNum; ++i) {
		if (hardware_read_order(i, HARDWARE_ORDER_UP)) {
			elevator->orders[i][ORDER_UP] = hardware_read_order(i, HARDWARE_ORDER_UP);
		}
		if (hardware_read_order(i, HARDWARE_ORDER_DOWN)) {
			elevator->orders[i][ORDER_DOWN] = hardware_read_order(i, HARDWARE_ORDER_DOWN);
		}
		if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)) {
			elevator->orders[i][ORDER_INTERNAL] = hardware_read_order(i, HARDWARE_ORDER_INSIDE);
		}
	}
	orders_lightOrders(elevator);
}

void orders_orderDone(Elevator* elevator) {
	if (elevator->state = AT_FLOOR) {
		elevator->orders[elevator->currentFloor] = {false, false, false};
	}
}


bool orders_stopAtFloor(Elevator* elevator) {
	if (elevator->direction == 1) {
		if (elevator->orders[elevator->currentFloor][ORDER_UP] || 
			elevator->orders[elevator->currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((orders_getDirection(elevator) == -1) &&
				elevator->orders[elevator->currentFloor][ORDER_DOWN]) {
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					return true;
				}
	}
	else if (elevator->direction == -1) {
		if (elevator->orders[elevator->currentFloor][ORDER_DOWN] || 
			elevator->orders[elevator->currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((orders_getDirection(elevator) == 1) &&
				elevator->orders[elevator->currentFloor][ORDER_UP]) {
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					return true;
				}
	}
	return false;
}

bool orders_activatedStopButton() {
	if (hardware_read_stop_signal()) {
		return true;
	}
	else {
		return false;
	}
}


