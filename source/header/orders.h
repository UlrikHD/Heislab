/*
* @page
* @brief
*/
#include "elevator.h"

#ifndef ORDERS_H
#define ORDERS_H
#define ORDER_DOWN 1
#define ORDER_UP 0
#define ORDER_INTERNAL 2




int order_getDirection(Elevator elevator);

bool orders_noOrders(Elevator elevator);

void orders_emptyOrders(Elevator elevator);

void getOrders(Elevator elevator);

bool orders_stopAtFloor(Elevator elevator);

#endif
