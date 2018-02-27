#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include "InputScanner.h"
#include "Motor.h"
#include "StateTable.h"
#include "GarageDoorController.h"

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
	InputScanner * inputScanner = new InputScanner();
	Motor * motor = new Motor();
    StateTable* stateTable = new StateTable();

//	while(true) {
//		switch(::INPUT) {
//			case RemoteButton:
//                stateTable->transition(RemoteButton);
//				pthread_mutex_lock( &::MUTEX );
//				::SHOULD_MOVE = ON;
//				::DIRECTION = ::DIRECTION == UP ? DOWN : UP;
//				::INPUT = None;
//				pthread_mutex_unlock( &::MUTEX );
//				break;
//			case FullOpen:
//				pthread_mutex_lock( &::MUTEX );
//				::SHOULD_MOVE = OFF;
//				::FULL_OPEN = true;
//				::INPUT = None;
//				pthread_mutex_unlock( &::MUTEX );
//				break;
//			case FullClose:
//				pthread_mutex_lock( &::MUTEX );
//				::SHOULD_MOVE = OFF;
//				::FULL_CLOSE = true;
//				::INPUT = None;
//				pthread_mutex_unlock( &::MUTEX );
//				break;
//			default:
//				break;
//		}
//	}

//	StateTable* stateTable = new StateTable();
//
//	GarageDoorController* ctrl = new GarageDoorController(stateTable);

	while(true) {
		switch(::INPUT) {
			case RemoteButton:
			case IRSensor:
			case MotorOC:
			case FullOpen:
			case FullClose:
				stateTable->transition(::INPUT);
				::INPUT = None;
				break;
			default:
				break;
		}
	}


	return EXIT_SUCCESS;
}
