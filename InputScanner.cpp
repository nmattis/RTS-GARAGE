/*
 * InputScanner.cpp
 *
 * Class responsible for managing user input to the system.
 */
#include "InputScanner.h"

/** creates an input scanner thread */
InputScanner::InputScanner() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&inputScanner, &attr, InputScanner::readUserInput, this);
}

/** destructor */
InputScanner::~InputScanner() {}

/**
 * Method that runs in a thread and takes the user input to fire
 * off control events to the garage door controller. These events
 * are motor over current simulation, IR sensor trip, and remote
 * button press simulation.
 */
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

/** Fires the Remote button press event */
void InputScanner::pushButton() {
	pthread_mutex_lock( &::MUTEX );
	::INPUT = RemoteButton;
	pthread_mutex_unlock( &::MUTEX );
}

/** Fires an IR Sensor Trip event */
void InputScanner::tripIR() {
	pthread_mutex_lock( &::MUTEX );
	::INPUT = IRSensor;
	pthread_mutex_unlock( &::MUTEX );
}

/** Fires a motor over current event */
void InputScanner::motorOverCurrent() {
	pthread_mutex_lock( &::MUTEX );
	::INPUT = MotorOC;
	pthread_mutex_unlock( &::MUTEX );
}
