/**
 * @file
 * @brief Library for functions related to orders and the elevator's queue system.
 */
#ifndef ORDERS_H
#define ORDERS_H

#include <stdbool.h>
#include "elevator.h"
#include "hardware.h"

#define ORDER_UP 0
#define ORDER_DOWN 1
#define ORDER_INTERNAL 2


/**
 * @brief Updates every order lights of the elevator
 *
 * @param[in] p_elevator    Elevator whose list will decide which order lights to be 
 * turned on/off.
 */
void orders_lightOrders(const Elevator* p_elevator);

/**
 * @brief Function that decides which way the Elevator will move.
 * 
 * Alongisde @c orders_stopAtFloor(), the main logic of the queue system.
 * The function will prioritise orders that is in its current path, 
 * assuming the Elevator will keep moving in its current direction.
 *
 * @param[in] p_elevator    Elevator whose orders will be evaluated.
 *
 * @return 1 if direction is upwards and -1 if downwards. If there are no orders 
 * the function will return back the value @p p_elevator already contains.
 */
int orders_getDirection(const Elevator* p_elevator);

/**
 * @brief Checks if the Elevator got any orders queued.
 *
 * @param[in] p_elevator    Elevator to be checked for queued orders.
 *
 * @return @c false if @p p_elevator got any orders queued, @c true if not.
 */
bool orders_noOrders(const Elevator* p_elevator);

/**
 * @brief Remove all orders queued and sets every entry in @c Elevator.orders 
 * to @c false.
 * 
 * The function will call on @c orders_lightOrders() at the end to update lights.
 *
 * @param[in, out] p_elevator    Elevator to have its orders removed,
 */
void orders_emptyOrders(Elevator* p_elevator);

/**
 * @brief Function that fetches every order.
 * 
 * The function will call on @c orders_lightOrders() at the end to update lights.
 *
 * @param[in, out] p_elevator    Elevator to recieve orders.
 */
void orders_getOrders(Elevator* p_elevator);

/**
 * @brief Function that erase orders in queue when the orders have been executed.
 *
 * @param[in, out] p_elevator    Elevator to have its queue updated.
 */
void orders_orderDone(Elevator* p_elevator);

/**
 * @brief Function that stops the elevator if there are appropiate orders on the floor.
 *
 * This function is alongside the @c orders_getDirection() the main logic of the
 * Elevator queue. This function will only call the Elevator to stop on the floor 
 * if there are orders on the floor that aligns with its current direction,
 * or regardless of direction if there are no orders past the current floor.
 * 
 * @param[in] p_elevator    Elevator to have its orders evaluated.
 * 
 * @warning While the function got a boolean value, this is only to let you know
 * if @p p_elevator will stop or not. The function will stop @p p_elevator without
 * any extra needed code.
 * 
 * @return @c true if @p p_elevator should stop, @c false if not.
 */
bool orders_stopAtFloor(const Elevator* p_elevator);

/**
 * @brief Simple function only meant for increasing the readability of the code, 
 * tells you if the stop button is pressed or not.
 * 
 * @return @c true if the stop button is pressed, @c false otherwise.
 */
bool orders_activatedStopButton();

/**
 * @brief Function that deal with orders on the same floor as the Elevator
 * currently sits still on.
 * 
 * This function was made to handle the special case of an order being placed at
 * the same floor as the Elevator is currently at. The function will reset the
 * @c Elevator.timer and set all orders on that floor to false in the queue.
 * The function @c orders_lightOrders() will also be called inside this function.
 * 
 * @param[in, out] p_elevator    Elevator to have its orders evaluated.
 * 
 * @warning This function will do the job of @c orders_orderDone() for the floor the
 * Elevator currently sits at. This means any orders that happen on the current
 * floor of the Elevator will immediately be set to false if this function is run.
 * 
 * @return @c true if @p p_elevator got any orders on its current floor,
 * @c false if no order on its current floor.
 */
bool orders_orderIsSameFloor(Elevator* p_elevator);

#endif
