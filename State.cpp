/*
 * State.cpp
 *
 * This file contains all state definitions and their entry and exit actions.
 * See the StateChart diagram in our documentation for explicit information.
 */
#include "State.h"
#include "IOPort.h"


void Closed::doEntryAction() {
	IOPort* ioManager = IOPort::getInstance();
	std::cout << std::endl << "Door Closed!" << std::endl;
	::FULL_CLOSE = true;
	::SHOULD_MOVE = false;
	// motor down 0 (1)
	ioManager->setOutputPinOff(BIT1);
}

void Closed::doExitAction() {
	::FULL_CLOSE = false;
}

void Opening::doEntryAction() {
	IOPort* ioManager = IOPort::getInstance();
	::SHOULD_MOVE = true;
	::DIRECTION = UP;
	// motor up 1
	ioManager->setOutputPinOn(BIT0);
}

void Opening::doExitAction() {
	IOPort* ioManager = IOPort::getInstance();
	::SHOULD_MOVE = false;
	// motor up 0
	ioManager->setOutputPinOff(BIT0);
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
	IOPort* ioManager = IOPort::getInstance();
	std::cout << std::endl << "IR Sensor ON" << std::endl;
	::SHOULD_MOVE = true;
	::IR_SENSOR = ON;
	::DIRECTION = DOWN;
	// motor down 1 (1), IR On 1 (2)
	ioManager->setOutputPinOn(BIT2);
	ioManager->setOutputPinOn(BIT1);
}

void Closing::doExitAction() {
	IOPort* ioManager = IOPort::getInstance();
	std::cout << std::endl << "IR Sensor OFF" << std::endl;
	::IR_SENSOR = OFF;
	// IR Off 0 (2)
	ioManager->setOutputPinOff(BIT1);
	ioManager->setOutputPinOff(BIT2);

}

void StoppedClosing::doEntryAction() {
	::SHOULD_MOVE = false;
}

void StoppedClosing::doExitAction() {}

void StoppedOpening::doEntryAction() {
	::SHOULD_MOVE = false;
}

void StoppedOpening::doExitAction() {}
