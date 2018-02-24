/*
 * StateTable.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef STATETABLE_H_
#define STATETABLE_H_

#include <vector>

#include "State.h"
#include "Transition.h"

class StateTable {
public:
	StateTable();
	virtual ~StateTable();
	State getCurrentState();
	Transition getNextTransition();

private:
	State currentState;
};

#endif /* STATETABLE_H_ */
