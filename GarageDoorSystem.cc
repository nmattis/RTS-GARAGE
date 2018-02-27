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

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
	::INPUT = None;
	InputScanner * inputScanner;
	Motor* motor;

	/** kick off our threads */
	inputScanner = new InputScanner();
	motor = new Motor();

	/** initialize the state machine */
    StateTable* stateTable = new StateTable();

    // look for actions to do
	while(true) {
		switch(::INPUT) {
			case RemoteButton:
			case IRSensor:
			case MotorOC:
			case FullOpen:
			case FullClose:
				// since we have a state machine with a method to check
				// events there is no need for extra logic, just cascade
				// and ensure the event gets passed
				stateTable->transition(::INPUT);
				::INPUT = None;
				break;
			default:
				break;
		}
	}

	return EXIT_SUCCESS;
}
