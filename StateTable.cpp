/*
 * StateTable.cpp
 *
 * Creates our state table and kicks of transitions when passed input
 * from the system.
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

/** creates the table and all transitions */
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

	// sets current state
	this->currentState = &closed;
}

/** destructor */
StateTable::~StateTable() {}

/** returns the systems current state */
State* StateTable::getState() {
	return this->currentState;
}

/**
 * executes the transition to a state given an event if
 * the current state allows.
 */
bool StateTable::transition(InputEvents event) {
	std::vector<std::pair<InputEvents, State*> > stateTrans = this->currentState->getTransitions();
	for(std::vector<std::pair<InputEvents, State*> >::iterator it = stateTrans.begin();	it != stateTrans.end();	++it) {
		if (it->first == event) {
			this->currentState->doExitAction();
			this->setState(it->second);
			currentState->doEntryAction();

			return true;
		}
	}

	return false;
}

/** sets current state of the state machine */
void StateTable::setState(State* newState) {
	this->currentState = newState;
}
