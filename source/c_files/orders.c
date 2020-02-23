#include "orders.h"

int order_getDirection(Elevator elevator) {
	if (elevator.direction == 1) {
		for (int i = elevator.floor; i < floorsNum; ++i) {
			if (elevator.orders[i][ORDER_UP]) {
				return 1;
			}
		}
		for (int i = elevator.floor; i < floorsNum; ++i) {
			if (elevator.orders[i][ORDER_DOWN]) {
				return 0;
			}
		}
		return -1;
	}

	else {
		for (int i = elevator.floor; i < floorsNum; ++i) {
			if (elevator.orders[i][ORDER_DOWN]) {
				return 0;
			}
		}
		for (int i = elevator.floor; i < floorsNum; ++i) {
			if (elevator.orders[i][ORDER_UP]) {
				return 1;
			}
		}
		return -1;
	}
}

int order_setMovement()