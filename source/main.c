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

int main() {/*
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
	
    signal(SIGINT, sigint_handler);

    Elevator* elevator;
	elevator->buttonNum = 3;
    elevator->HARDWARE_NUMBER_OF_FLOORS;
    elevator->doorOpenTime = 6000000; //in microseconds
    elevator->obstruction = false;
    elevator->state = IDLE;

	while (true) {
		if (orders_activatedStopButton()) {
			elevator->state = EMERGENCY_STOP;
			state_stateSwitch(elevator);
		}
		switch (elevator->state) {
			case IDLE:
				state_findFloor(elevator);
				orders_getOrders(elevator);
				if (!orders_noOrders(elevator)) {
					elevator->direction = orders_getOrders(elevator);
					elevator->state = MOVING;
					state_stateSwitch(elevator);
				}
				break;
			case MOVING:
				orders_getOrders(elevator);
				elevator->direction = orders_getDirection(elevator);
				if (state_atFloor != -1) {
					elevator->currentFloor = state_atFloor;
					if (orders_stopAtFloor(elevator)) {
						elevator->state = AT_FLOOR;
						orders_orderDone(elevator);
						state_stateSwitch(elevator);
					}
					else {
						if (order_getDirection(p_elev) == 1) {
							hardware_command_movement(HARDWARE_MOVEMENT_UP);
							p_elev->nextFloor += p_elev->currentFloor;
				}
					else {
							hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
							p_elev->nextFloor -= p_elev->currentFloor;
				}
					}
				}
				break;
			case AT_FLOOR:
				orders_getOrders(elevator);
				elevator->direction = orders_getDirection(elevator);
				if (state_timerDone && !elevator_doorObstructed) {
					hardware_command_door_open(0);
					if (orders_emptyOrders) {
						elevator->state = IDLE;
						state_stateSwitch(elevator);
					}
					else {
						elevator->state = MOVING;
						state_stateSwitch(elevator);
					}
				}
				break;
			case EMERGENCY_STOP:
				if (!orders_activatedStopButton()) {
					hardware_command_stop_light(0);
					elevator->state = IDLE;
					state_stateSwitch(elevator);
				}
				break;
			
			default:
				elevator->state = IDLE;
				state_stateSwitch(elevator);
				break;
		}
		
	}*/
	printf("n");
    return 0;
}
