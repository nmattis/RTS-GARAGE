#include <cstdlib>
#include <iostream>
#include "InputScanner.h"
#include "Motor.h"
#include "SharedVars.h"

InputEvents INPUT = None;

bool DIRECTION = 0;
bool SHOULD_MOVE = 0;

int MOTOR_POS = 0;

bool FULL_OPEN = 0;
bool FULL_CLOSE = 1;

pthread_mutex_t inputScannerMutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {

	InputScanner * inputScanner = new InputScanner();
	Motor * motor = new Motor();

	while(true) {

		switch(::INPUT) {
			case RemoteButton:
				std::cout << "Remote button!" << std::endl;
				break;
			case IRSensor:
				std::cout << "IR Sensor!" << std::endl;
				break;
			case MotorOC:
				std::cout << "OC Sensor!" << std::endl;
				break;
			default:
				break;
		}
		pthread_mutex_unlock( &inputScannerMutex );
		::INPUT = None;
	}
	return EXIT_SUCCESS;
}
