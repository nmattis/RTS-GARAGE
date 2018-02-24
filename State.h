/*
 * State.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef STATE_H_
#define STATE_H_
#include "Transition.h"

class State {
public:
	State(int ID);
	virtual ~State();
	virtual void doEntryAction();
	virtual void doExitAction();
	int getStateID() {
		return StateID;
	};

protected:
	int StateID;
};

#endif /* STATE_H_ */
