/**
 * GarageDoorSystem.cc
 *
 * The controller or context for the entire system. Responsible for
 * communicating state and actions from the input scanner to the
 * state table and motor.
 */
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <sys/neutrino.h>
#include "InputScanner.h"
#include "Motor.h"
#include "StateTable.h"

/** initialize our inputs */
InputEvents INPUT = None;

bool DIRECTION = DOWN;
bool SHOULD_MOVE = OFF;
bool IR_SENSOR = OFF;

int MOTOR_POS = 0;

bool FULL_OPEN = false;
bool FULL_CLOSE = true;
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <stdio.h>
#define IO_PORT_SIZE 1
#define PORT_A_ON (16)
#define PORT_B_OFF (253)
#define CTRL_ADDRESS (0x28B)
#define PORT_A_ADDRESS (0x288)
#define PORT_B_ADDRESS (0x289)
uintptr_t ctrl_handle;
uintptr_t port_b_output;
uintptr_t port_a_input;

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1) {
		perror("Failed to get I/O access permission");
		return 1;
	}
	ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);

	if(ctrl_handle == MAP_DEVICE_FAILED) {
		perror("Failed to map control register");
		return 0;
	}
	// Port A input, Port B output
	uint8_t ctrl_port_value = in8(ctrl_handle);
	ctrl_port_value |= PORT_A_ON;
	ctrl_port_value &= PORT_B_OFF;
	out8( ctrl_handle, ctrl_port_value );

	// READ AND WRITE
	port_a_input = mmap_device_io(IO_PORT_SIZE, PORT_A_ADDRESS);
	port_b_output = mmap_device_io(IO_PORT_SIZE, PORT_B_ADDRESS);

	// 00000000
	//B76543210
	uint8_t port_b_input;
	uint8_t port_b = in8(port_b_input);

	uint8_t reset_toggle = 8;
	uint8_t x = (port_b | reset_toggle);
	out8(port_b_output, x);

	uint8_t on = 3;
	uint8_t off = 252;
//
//	::INPUT = None;
//	InputScanner * inputScanner;
//	Motor* motor;
//
//	/** kick off our threads */
//	inputScanner = new InputScanner();
//	motor = new Motor();
//
//	/** initialize the state machine */
//    StateTable* stateTable = new StateTable();

    // look for actions to do
	while(true) {
		port_b = in8(port_b_output);
		std::cout << "I\'m running" << std::endl;
		uint8_t x = (port_b | on);
		out8(port_b_output, x);
		usleep(1000000);
		uint8_t y = (port_b & off);
		port_b = in8(port_b_output);
		out8(port_b_output, y);
		usleep(1000000);

//		switch(::INPUT) {
//			case RemoteButton:
//			case IRSensor:
//			case MotorOC:
//			case FullOpen:
//			case FullClose:
//				// since we have a state machine with a method to check
//				// events there is no need for extra logic, just cascade
//				// and ensure the event gets passed
//				stateTable->transition(::INPUT);
//				::INPUT = None;
//				break;
//			default:
//				break;
//		}


	}

	return EXIT_SUCCESS;
}
