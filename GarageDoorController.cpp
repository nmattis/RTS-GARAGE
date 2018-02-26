/*
 * GarageDoorController.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: nxm5757
 */

#include "GarageDoorController.h"
#include "SharedVars.h"

GarageDoorController::GarageDoorController(StateTable* stateTable) {
	this->stateTable = stateTable;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&controller, &attr, GarageDoorController::doTheControlling, this);
}

GarageDoorController::~GarageDoorController() {
	// TODO Auto-generated destructor stub
}

void* GarageDoorController::doTheControlling(void* instance) {
	while(true) {
		switch(::INPUT) {
			case RemoteButton:
			case IRSensor:
			case MotorOC:
			case FullOpen:
			case FullClose:
				((GarageDoorController*)instance)->stateTable->transition(::INPUT);
				::INPUT = None;
				break;
			default:
				break;
		}
	}

	return 0;
}
