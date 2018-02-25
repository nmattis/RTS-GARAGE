/*
 * State.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <vector>
#include <iostream>
#include "SharedVars.h"

class State {
public:
	virtual void doEntryAction() = 0;
	virtual void doExitAction() = 0;
	void setTransition(InputEvents event, State* state) {
		this->transitions.push_back(std::make_pair(event, state));
	};
	std::vector<std::pair<InputEvents,State*> > getTransitions() {
		return this->transitions;
	};

protected:
	std::vector<std::pair<InputEvents,State*> > transitions;
};

class Closed : public State {
public:
	void doEntryAction();
	void doExitAction();
};

class Opening : public State {
public:
	void doEntryAction();
	void doExitAction();
};

class Opened : public State {
public:
	void doEntryAction();
	void doExitAction();
};

class Closing : public State {
public:
	void doEntryAction();
	void doExitAction();
};

class StoppedClosing : public State {
public:
	void doEntryAction();
	void doExitAction();
};

class StoppedOpening : public State {
public:
	void doEntryAction();
	void doExitAction();
};

#endif /* STATE_H_ */
