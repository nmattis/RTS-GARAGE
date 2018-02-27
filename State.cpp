/*
 * State.cpp
 *
 * This file contains all state definitions and their entry and exit actions.
 * See the StateChart diagram in our documentation for explicit information.
 */
#include "State.h"

void Closed::doEntryAction() {
	std::cout << std::endl << "Door Closed!" << std::endl;
	::FULL_CLOSE = true;
	::SHOULD_MOVE = false;
}

void Closed::doExitAction() {
	::FULL_CLOSE = false;
}

void Opening::doEntryAction() {
	::SHOULD_MOVE = true;
	::DIRECTION = UP;
}

void Opening::doExitAction() {
	::SHOULD_MOVE = false;
}

void Opened::doEntryAction() {
	std::cout << std::endl << "Door Open!" << std::endl;
	::FULL_OPEN = true;
	::SHOULD_MOVE = false;
}

void Opened::doExitAction() {
	::FULL_OPEN = false;
}

void Closing::doEntryAction() {
	std::cout << std::endl << "IR Sensor ON" << std::endl;
	::SHOULD_MOVE = true;
	::IR_SENSOR = ON;
	::DIRECTION = DOWN;
}

void Closing::doExitAction() {
	std::cout << std::endl << "IR Sensor OFF" << std::endl;
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
