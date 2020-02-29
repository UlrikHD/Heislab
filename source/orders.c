#include "orders.h"

void orders_lightOrders(Elevator* p_elevator) {
	for (int i = 0; i < p_elevator->floorsNum; ++i) {
		hardware_command_order_light(i, HARDWARE_ORDER_UP, p_elevator->orders[i][ORDER_UP]);
		hardware_command_order_light(i, HARDWARE_ORDER_DOWN, p_elevator->orders[i][ORDER_DOWN]);
		hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, p_elevator->orders[i][ORDER_INTERNAL]);
	}
}

int orders_getDirection(Elevator* p_elevator) {
	if (p_elevator->direction == 1) {
		for (int i = p_elevator->currentFloor + 1; i < p_elevator->floorsNum; ++i) {
			for (int j = 0; j < p_elevator->buttonNum; ++j) {
				if (p_elevator->orders[i][j]) {
					return 1;
				}
			}
		}
		for (int i = p_elevator->currentFloor; i >= 0; --i) {
			for (int j = 0; j < p_elevator->buttonNum; ++j) {
				if (p_elevator->orders[i][j]) {
					return -1;
				}
			}
		}
	}

	else {
		for (int i = p_elevator->currentFloor - 1; i >= 0; --i) {
			for (int j = 0; j < p_elevator->buttonNum; ++j) {
				if (p_elevator->orders[i][j]) {
					return -1;
				}
			}
		}
		for (int i = p_elevator->currentFloor; i < p_elevator->floorsNum; ++i) {
			for (int j = 0; j < p_elevator->buttonNum; ++j) {
				if (p_elevator->orders[i][j]) {
					return 1;
				}
			}
		}
	}
	return p_elevator->direction;
}

bool orders_noOrders(Elevator* p_elevator) {
	for (int i = 0; i < p_elevator->floorsNum; ++i) {
		for (int j = 0; j < p_elevator->buttonNum; ++j) {
			if (p_elevator->orders[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void orders_emptyOrders(Elevator* p_elevator) {
	for (int i = 0; i < p_elevator->floorsNum; ++i) {
		for (int j = 0; j < p_elevator->buttonNum; ++j) {
			p_elevator->orders[i][j] = false;
		}
	}
	orders_lightOrders(p_elevator);
}

void orders_getOrders(Elevator* p_elevator) {
	for (int i = 0; i < p_elevator->floorsNum; ++i) {
		if (hardware_read_order(i, HARDWARE_ORDER_UP)) {
			p_elevator->orders[i][ORDER_UP] = hardware_read_order(i, HARDWARE_ORDER_UP);
		}
		if (hardware_read_order(i, HARDWARE_ORDER_DOWN)) {
			p_elevator->orders[i][ORDER_DOWN] = hardware_read_order(i, HARDWARE_ORDER_DOWN);
		}
		if (hardware_read_order(i, HARDWARE_ORDER_INSIDE)) {
			p_elevator->orders[i][ORDER_INTERNAL] = hardware_read_order(i, HARDWARE_ORDER_INSIDE);
		}
	}
	orders_lightOrders(p_elevator);
}

void orders_orderDone(Elevator* p_elevator) {
	if (p_elevator->state == AT_FLOOR) {
		for (int i = 0; i < p_elevator->buttonNum; ++i) {
			p_elevator->orders[p_elevator->currentFloor][i] = false;
		}
	}
}

bool orders_stopAtFloor(Elevator* p_elevator) {
	if (p_elevator->direction == 1) {
		if (p_elevator->orders[p_elevator->currentFloor][ORDER_UP] || 
			p_elevator->orders[p_elevator->currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((orders_getDirection(p_elevator) == -1) &&
				p_elevator->orders[p_elevator->currentFloor][ORDER_DOWN]) {
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					return true;
				}
	}
	else if (p_elevator->direction == -1) {
		if (p_elevator->orders[p_elevator->currentFloor][ORDER_DOWN] || 
			p_elevator->orders[p_elevator->currentFloor][ORDER_INTERNAL]) {
				hardware_command_movement(HARDWARE_MOVEMENT_STOP);
				return true;
			}
		else if ((orders_getDirection(p_elevator) == 1) &&
				p_elevator->orders[p_elevator->currentFloor][ORDER_UP]) {
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


