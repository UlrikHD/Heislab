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


    int orders[floorsNum][buttonNum]

} Elevator

clock_t g_timer;


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
        if (hardware_read_stop_signal()) {
            elevator.g_state = STOP;
            state_stateSwitch(&elevator);
        }
        switch (order_getDirection(elevator)) {
            case 1: elevator.g_state(MOVING_UP); break;
            case 0: elevator.g_state(AT_FLOOR); break;
            case -1: elevator.g_state(MOVING_DOWN); break;
        }
        state_stateSwitch(&elevator);
        
    }






	while (state_getAtFloor()!=3) {
		
	};
    state_setState(IDLE);
    clear_all_order_lights();











    

    return 0;
}
