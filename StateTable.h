/*
 * StateTable.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef STATETABLE_H_
#define STATETABLE_H_

#include "State.h"
#include "SharedVars.h"
#include <vector>

class StateTable {
public:
	StateTable();
	virtual ~StateTable();
	State* getState();
	bool transition(InputEvents event);

private:
	State* currentState;
	void setState(State* newState);
};

#endif /* STATETABLE_H_ */
