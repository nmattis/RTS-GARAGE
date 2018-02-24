/*
 * InputScanner.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#include "InputScanner.h"

InputScanner::InputScanner() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&inputScanner, &attr, &InputScanner::readUserInput, this);
}

InputScanner::~InputScanner() {
	// TODO
}

void* InputScanner::readUserInput(void* instance) {
	while(true) {
		std::cout << std::endl << "Enter command: ";

		char keypressed;
		std::cin >> keypressed;

		switch(keypressed) {
			case 'm':
				std::cout << "Simulating Motor Overcurrent..." << std::endl;
				((InputScanner*)instance)->motorOverCurrent();
				break;
			case 'i':
				std::cout << "Simulating IR Sensor Trip..." << std::endl;
				((InputScanner*)instance)->tripIR();
				break;
			case 'r':
				std::cout << "Simulating Remote Push Button..." << std::endl;
				((InputScanner*)instance)->pushButton();
				break;
			default:
				std::cout << "Valid Inputs are:" << std::endl;
				std::cout << "    m: Simulate Motor Overcurrent" << std::endl;
				std::cout << "    i: Simulate IR Sensor Trip" << std::endl;
				std::cout << "    r: Simulate Remote Push Button" << std::endl;
		}
	}

	return 0;
}

void InputScanner::pushButton() {
	pthread_mutex_lock( &::inputScannerMutex );
	::INPUT = RemoteButton;
	pthread_mutex_unlock( &::inputScannerMutex );
}

void InputScanner::tripIR() {
	pthread_mutex_lock( &::inputScannerMutex );
	::INPUT = IRSensor;
	pthread_mutex_unlock( &::inputScannerMutex );
}

void InputScanner::motorOverCurrent() {
	pthread_mutex_lock( &::inputScannerMutex );
	::INPUT = MotorOC;
	pthread_mutex_unlock( &::inputScannerMutex );
}
