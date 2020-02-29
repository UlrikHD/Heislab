/**
 * @file
 * @brief Main file that creates the elevator program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


#include "hardware.h"
#include "state.h"
#include "orders.h"
#include "elevator.h"


static void clear_all_order_lights() {
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++) {
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

static void sigint_handler(int sig) {
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main() {
	//Checks to make sure everything works fine with hardware
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
	clear_all_order_lights();
    signal(SIGINT, sigint_handler);
	//Hardware checks done

	//Make eleevator ready
	Elevator heis;
	Elevator* p_elevator;
	elevator_initElevator(&heis);
	p_elevator = &heis;
	while (elevator_atFloor() == -1) {
		state_findFloor(p_elevator);
	
	}
	//Elevator setup done

	while (true) {
		if (orders_activatedStopButton()) {
			p_elevator->state = EMERGENCY_STOP;
			state_stateSwitch(p_elevator);
		}
		switch (p_elevator->state) {
			case IDLE:
				state_findFloor(p_elevator);
				orders_getOrders(p_elevator);
				if (!orders_noOrders(p_elevator)) {
					p_elevator->direction = orders_getDirection(p_elevator);
					p_elevator->state = MOVING;
					state_stateSwitch(p_elevator);
				}
				break;
			case MOVING:
				orders_getOrders(p_elevator);
				p_elevator->direction = orders_getDirection(p_elevator);
				if (elevator_atFloor() != -1) {
					elevator_updateFloors(p_elevator);
					if (orders_stopAtFloor(p_elevator)) {
						p_elevator->state = AT_FLOOR;
						orders_orderDone(p_elevator);
						state_stateSwitch(p_elevator);
					}
					else {
						if (orders_getDirection(p_elevator) == 1) {
							hardware_command_movement(HARDWARE_MOVEMENT_UP);
						}
						else {
							hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
						}
					}
				}
				break;
			case AT_FLOOR:
				orders_getOrders(p_elevator);
				orders_orderIsSameFloor(p_elevator);
				if (!elevator_doorObstructed(p_elevator) && state_timerDone(p_elevator)) {
					hardware_command_door_open(0);
					p_elevator->direction = orders_getDirection(p_elevator);
					if (orders_noOrders(p_elevator)) {
						p_elevator->state = IDLE;
						state_stateSwitch(p_elevator);
					}
					else {
						p_elevator->state = MOVING;
						state_stateSwitch(p_elevator);
					}
				}
				break;
			case EMERGENCY_STOP:
				if (!orders_activatedStopButton()) {
					hardware_command_stop_light(0);
					orders_getOrders(p_elevator);
					bool orderSameFloor = orders_orderIsSameFloor(p_elevator);
					if (orderSameFloor){
						p_elevator->state = AT_FLOOR;
						state_stateSwitch(p_elevator);
						}
					if (!elevator_doorObstructed(p_elevator) && state_timerDone(p_elevator)) {
						hardware_command_door_open(0);
						if (!orders_noOrders(p_elevator)) {
							if (p_elevator->currentFloor < p_elevator->nextFloor) {
								p_elevator->direction = 1;
							}
							else {
								p_elevator->direction = -1;
							}
							p_elevator->state = MOVING;
							state_stateSwitch(p_elevator);
						}
					}
				}
				break;
			default: //unødvendig
				p_elevator->state = IDLE;
				state_stateSwitch(p_elevator);
				break;
		}
		
	}
    return 0;
}
