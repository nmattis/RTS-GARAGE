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
	pthread_create(&inputScanner, &attr, InputScanner::readUserInput, this);
}

InputScanner::~InputScanner() {
	// TODO
}

void* InputScanner::readUserInput(void* instance) {
	char keypressed;
	std::cout << std::endl << "Enter command any time..." << std::endl;
	std::cout << "Valid Inputs are:" << std::endl;
	std::cout << "    m: Simulate Motor Overcurrent" << std::endl;
	std::cout << "    i: Simulate IR Sensor Trip" << std::endl;
	std::cout << "    r: Simulate Remote Push Button" << std::endl;
	while(true) {
		std::cin >> keypressed;
		std::cin.ignore();
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
	pthread_mutex_lock( &::MUTEX );
	::INPUT = RemoteButton;
	pthread_mutex_unlock( &::MUTEX );
}

void InputScanner::tripIR() {
	pthread_mutex_lock( &::MUTEX );
	::INPUT = IRSensor;
	pthread_mutex_unlock( &::MUTEX );
}

void InputScanner::motorOverCurrent() {
	pthread_mutex_lock( &::MUTEX );
	::INPUT = MotorOC;
	pthread_mutex_unlock( &::MUTEX );
}
