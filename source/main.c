/**
 * @file
 * @brief Main file that creates the elevator program.
 */

/*! \mainpage Index Page for Heisprosjekt - TTK4235
 *
 * \section intro_sec Introduction
 *
 * This projects contains 7 files written by the Aksel Næstby and Ulrik H.Digerud,
 * and 5 files provided by the course TTK4235. This Index page contains
 * documentation for the files:
 * 
 *  - main.c
 *  - state.h
 *  - state.c
 *  - orders.h
 *  - orders.c
 *  - elevator.h
 *  - elevator.c
 *  - hardware.h - provided and commented by the course's TA
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Clone the git repository https://github.com/UlrikHD/Heislab
 * 
 * \subsection step2 Step 2: Open the terminal and type "make" inside the "Heislab"-folder.
 * 
 * \subsection step3 Step 3: Run the program by typing "./elevator" in the same folder.
 *
 * \section uninstall_sec Uninstalling
 * 
 * \subsection step4 Inside the "Heislab"-folder: Type "make clean" in the terminal.
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
	//Hardware checks finished

	//Make elevator ready
	Elevator heis;
	Elevator* p_elevator;
	elevator_initElevator(&heis);
	p_elevator = &heis;
	while (elevator_atFloor() == -1) {
		state_findFloor(p_elevator);
	
	}
	//Elevator setup done - defined state found

	while (true) {
		switch (p_elevator->state) {
			case IDLE:
				state_findFloor(p_elevator);
				orders_getOrders(p_elevator);
				if (!orders_noOrders(p_elevator)) {
					p_elevator->direction = orders_getDirection(p_elevator);
					p_elevator->state = MOVING;
					state_stateSwitch(p_elevator);
				}
				state_checkStop(p_elevator);
				break;
			case MOVING:
				orders_getOrders(p_elevator);
				//p_elevator->direction = orders_getDirection(p_elevator);
				if (elevator_atFloor() != -1) {
					elevator_updateFloors(p_elevator);
					if (orders_stopAtFloor(p_elevator)) {
						p_elevator->state = AT_FLOOR;
						orders_orderDone(p_elevator);
						state_stateSwitch(p_elevator);
					}
					else {
						state_continueMovement(p_elevator);
					}
				}
				state_checkStop(p_elevator);
				break;
			case AT_FLOOR:
				orders_getOrders(p_elevator);
				orders_orderIsSameFloor(p_elevator);
				if (!elevator_doorObstructed(p_elevator) && elevator_timerDone(p_elevator)) {
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
				state_checkStop(p_elevator);
				break;
			case EMERGENCY_STOP:
				state_checkStop(p_elevator);
				if (!orders_activatedStopButton()) {
					hardware_command_stop_light(0);
					orders_getOrders(p_elevator);
					bool orderSameFloor = orders_orderIsSameFloor(p_elevator);
					if (orderSameFloor){
						p_elevator->state = AT_FLOOR;
						state_stateSwitch(p_elevator);
					}
					if (!elevator_doorObstructed(p_elevator) && elevator_timerDone(p_elevator)) {
						hardware_command_door_open(0);
						state_getOrdersInStop(p_elevator);
					}
				}
				break;
			default:
				p_elevator->state = IDLE;
				state_stateSwitch(p_elevator);
				break;
		}
		
	}
    return 0;
}
