/*
 * Transition.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_
#include "State.h"

class Transition {
public:
	Transition(int ID);
	virtual ~Transition();
	virtual bool guard();
	virtual State getNextState();
	int getTransitionID() {
		return TransitionID;
	};

protected:
	int TransitionID;
};

#endif /* TRANSITION_H_ */
