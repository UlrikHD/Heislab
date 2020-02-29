#ifndef ORDERS_H
#define ORDERS_H

#include "elevator.h"
#include <stdbool.h>
#include "hardware.h"

#define ORDER_DOWN 1
#define ORDER_UP 0
#define ORDER_INTERNAL 2


void orders_lightOrders(Elevator* p_elevator);

int orders_getDirection(Elevator* p_elevator);

bool orders_noOrders(Elevator* p_elevator);

void orders_emptyOrders(Elevator* p_elevator);

void orders_getOrders(Elevator* p_elevator);

void orders_orderDone(Elevator* p_elevator);

bool orders_stopAtFloor(Elevator* p_elevator);

bool orders_activatedStopButton();

void orders_orderIsSameFloor(Elevator* p_elevator);

#endif
