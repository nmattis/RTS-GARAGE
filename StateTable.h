/*
 * StateTable.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef STATETABLE_H_
#define STATETABLE_H_

#include "State.h"

class StateTable {
public:
	StateTable();
	virtual ~StateTable();
	State* getState();
	void setState();

private:
	State* currentState;
};

#endif /* STATETABLE_H_ */
