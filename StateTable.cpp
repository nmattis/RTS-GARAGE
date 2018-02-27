/*
 * StateTable.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#include "State.h"
#include "StateTable.h"
#include "SharedVars.h"

// initialize everything
Closed closed;
Opening opening;
Opened opened;
Closing closing;
StoppedClosing stoppedClosing;
StoppedOpening stoppedOpening;

StateTable::StateTable() {
	// set transitions
	closed.setTransition(RemoteButton, &opening);

	opening.setTransition(FullOpen, &opened);
	opening.setTransition(MotorOC, &stoppedOpening);
	opening.setTransition(RemoteButton, &stoppedOpening);

	opened.setTransition(RemoteButton, &closing);

	closing.setTransition(FullClose, &closed);
	closing.setTransition(RemoteButton, &stoppedClosing);
	closing.setTransition(MotorOC, &opening);
	closing.setTransition(IRSensor, &opening);

	stoppedOpening.setTransition(RemoteButton, &closing);
	stoppedClosing.setTransition(RemoteButton, &opening);

	this->currentState = &closed;
}

State* StateTable::getState() {
	return this->currentState;
}

bool StateTable::transition(InputEvents event) {
	std::vector<std::pair<InputEvents, State*> > stateTrans = this->currentState->getTransitions();
	for(std::vector<std::pair<InputEvents, State*> >::iterator it = stateTrans.begin();	it != stateTrans.end();
			++it
	) {
		if (it->first == event) {
			this->currentState->doExitAction();
			this->setState(it->second);
			currentState->doEntryAction();

			return true;
		}
	}

	return false;
}

void StateTable::setState(State* newState) {
	this->currentState = newState;
}

StateTable::~StateTable() {
	// TODO Auto-generated destructor stub
}

