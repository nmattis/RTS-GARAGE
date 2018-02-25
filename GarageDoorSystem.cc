#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include "InputScanner.h"
#include "Motor.h"

InputEvents INPUT = None;

bool DIRECTION = false;
bool SHOULD_MOVE = false;
bool IR_SENSOR = false;

int MOTOR_POS = 0;

bool FULL_OPEN = false;
bool FULL_CLOSE = true;

pthread_mutex_t inputScannerMutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {

	InputScanner * inputScanner = new InputScanner();
	Motor * motor = new Motor();

	while(true) {

		switch(::INPUT) {
			case RemoteButton:
				std::cout << "Remote button!" << std::endl;
				::INPUT = None;
				break;
			case IRSensor:
				std::cout << "IR Sensor!" << std::endl;
				::INPUT = None;
				break;
			case MotorOC:
				std::cout << "OC Sensor!" << std::endl;
				::INPUT = None;
				break;
			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}
