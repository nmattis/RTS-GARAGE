/*
 * State.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: nxm5757
 */

#include "State.h"

void Closed::doEntryAction() {
	std::cout << "Door Closed!" << std::endl;
	::FULL_CLOSE = true;
	::SHOULD_MOVE = false;
}

void Closed::doExitAction() {
	::FULL_CLOSE = false;
}

void Opening::doEntryAction() {
	std::cout << "Motor moving UP!" << std::endl;
	::SHOULD_MOVE = true;
	::DIRECTION = UP;
}

void Opening::doExitAction() {
	::SHOULD_MOVE = false;
}

void Opened::doEntryAction() {
	std::cout << "Door Open!" << std::endl;
	::FULL_OPEN = true;
	::SHOULD_MOVE = false;
}

void Opened::doExitAction() {
	::FULL_OPEN = false;
}

void Closing::doEntryAction() {
	std::cout << "IR Sensor ON" << std::endl;
	std::cout << "Motor moving DOWN!" << std::endl;
	::SHOULD_MOVE = true;
	::IR_SENSOR = ON;
	::DIRECTION = DOWN;
}

void Closing::doExitAction() {
	std::cout << "IR Sensor OFF" << std::endl;
	::IR_SENSOR = OFF;
}

void StoppedClosing::doEntryAction() {
	::SHOULD_MOVE = false;
}

void StoppedClosing::doExitAction() {}

void StoppedOpening::doEntryAction() {
	::SHOULD_MOVE = false;
}

void StoppedOpening::doExitAction() {}
