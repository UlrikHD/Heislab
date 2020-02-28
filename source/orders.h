#ifndef ORDERS_H
#define ORDERS_H

#include "elevator.h"
#include <stdbool.h>
#include "hardware.h"

#define ORDER_DOWN 1
#define ORDER_UP 0
#define ORDER_INTERNAL 2

void orders_lightOrders(Elevator* elevator);

int orders_getDirection(Elevator* elevator);

bool orders_noOrders(Elevator* elevator);

void orders_emptyOrders(Elevator* elevator);

void orders_getOrders(Elevator* elevator);

void orders_orderDone(Elevator* elevator);

bool orders_stopAtFloor(Elevator* elevator);

bool orders_activatedStopButton();

#endif
