/*
 * InputScanner.cpp
 *
 * Class responsible for managing user input to the system.
 */
#include "InputScanner.h"
#include "IOPort.h"

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
	IOPort* ioManager = IOPort::getInstance();
	uint8_t buttonPressed;
	uint8_t previousInput = 0;
	while(true) {
		buttonPressed = ioManager->readPort('A');
		if ((buttonPressed & BIT0) != 0 && (previousInput & BIT0) == 0) {
			//FULL OPEN
			::INPUT = FullOpen;
		}
		if ((buttonPressed & BIT1) != 0 && ((previousInput & BIT1) == 0)) {
			//FULL CLOSED
			::INPUT = FullClose;
		}
		if ((buttonPressed & BIT2) != 0 && ((previousInput & BIT2) == 0)) {
			//IR TRIPPED
			std::cout << "Simulating IR Sensor Trip..." << std::endl;
			((InputScanner*)instance)->tripIR();
		}
		if ((buttonPressed & BIT3) != 0 && ((previousInput & BIT3) == 0)) {
			//OVERCURRENT
			std::cout << "Simulating Motor Overcurrent..." << std::endl;
			((InputScanner*)instance)->motorOverCurrent();
		}
		if ( ((buttonPressed & BIT4) != 0) && ((previousInput & BIT4) == 0) ) {
			//REMOTE BUTTON
			std::cout << "Simulating Remote Push Button..." << std::endl;
			((InputScanner*)instance)->pushButton();
		}

		previousInput = buttonPressed;
		usleep(250);  // try 100 if problems
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
