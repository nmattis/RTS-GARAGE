/*
 * GarageDoorController.h
 *
 *  Created on: Feb 25, 2018
 *      Author: nxm5757
 */

#ifndef GARAGEDOORCONTROLLER_H_
#define GARAGEDOORCONTROLLER_H_

#include "SharedVars.h"
#include "StateTable.h"
#include <pthread.h>

class GarageDoorController {
public:
	pthread_t controller;
	StateTable* stateTable;
	GarageDoorController(StateTable* stateTable);
	virtual ~GarageDoorController();
	static void* doTheControlling(void* instance);
};


#endif /* GARAGEDOORCONTROLLER_H_ */
