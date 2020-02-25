#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "hardware.h"
#include "state.h"
//#include "order.h"


typedef struct {
    int g_floor;
    int g_above;
    int g_direction;
    int g_atFloor;
    State g_state;
    clock_t g_timer;
    int g_timerDone;

    int orders[floorsNum][buttonNum]

} Elevator



static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
	
    signal(SIGINT, sigint_handler);

    if(2){
        printf("true");
    }
    else {
        printf("false");
    }



    Elevator elevator;

    while (state_atFloor() = -1) {
        hardware_command_movement(HardwareMovement HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HardwareMovement HARDWARE_MOVEMENT_STOP);


    elevator.g_atFloor = 1;
    elevator.g_floor = state_atFloor();
    elevator.g_above = 1;
    elevator.g_direction = 0;
    elevator.g_state = IDLE;


    while (1) {
        state_checkStopButton(&elevator);
        switch (order_getDirection(elevator)) {
            case 1: elevator.g_state = MOVING_UP; break;
            case 0: elevator.g_state = AT_FLOOR; break;
            case -1: elevator.g_state = MOVING_DOWN; break;
        }
        state_stateSwitch(&elevator);
        while (!order_queueIsEmpty()) {
            int floor = state_atFloor();
            if (floor > -1) {
                elevator.g_atFloor = 1;
                elevator.g_floor = floor;
                elevator.g_above = 0;

                int goOut = hardware_read_order(floor, HardwareOrder HARDWARE_ORDER_INSIDE);
                if (goOut) {
                    State temp = elevator.g_state;
                    elevator.g_state = AT_FLOOR;
                    state_stateSwitch(&elevator);
                    if (elevator.g_timerDone) {
                        if (order_queueIsEmpty()) {
                            elevator.g_state = IDLE;
                        }
                        else {
                            elevator.g_state = temp;
                        }
                        state_stateSwitch(&elevator);
                    }
                }

                switch (elevator.g_state) {
                    case MOVING_DOWN: {
                        int goDown = hardware_read_order(floor, HardwareOrder HARDWARE_ORDER_DOWN);
                        if (goDown) {
                            elevator.g_state = AT_FLOOR;
                            state_stateSwitch(&elevator);
                            if (state_timerDone(3, &elevator)) {
                                elevator.g_state = MOVING_DOWN;
                                state_checkStopButton(&elevator);
                                hardware_command_movement(HardwareMovement HARDWARE_MOVEMENT_DOWN);
                            }
                        }
                        break;
                    }
                    case MOVING_UP: {
                        int goUp = hardware_read_order(floor, HardwareOrder HARDWARE_ORDER_UP);
                        if (goUp) {
                            elevator.g_state = AT_FLOOR;
                            state_stateSwitch(&elevator);
                            if (state_timerDone(3, &elevator) && !hardware_read_obstruction_signal) {
                                hardware_command_door_open(0);
                                elevator.g_state = MOVING_UP;
                                state_checkStopButton(&elevator);
                                hardware_command_movement(HardwareMovement HARDWARE_MOVEMENT_UP);
                            }
                        }
                        g_above = 1;
                        break;
                    }
                }
                elevator.g_atFloor = 0;
            }
        }
        state_stateSwitch(&elevator);
        
    }






	while (state_getAtFloor()!=3) {
		
	};
    state_setState(IDLE);
    clear_all_order_lights();




              

    return 0;
}
