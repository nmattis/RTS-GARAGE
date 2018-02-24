/*
 * InputScanner.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef INPUTSCANNER_H_
#define INPUTSCANNER_H_

#include <pthread.h>
#include <iostream>

#include "SharedVars.h"

class InputScanner {
public:
	pthread_t inputScanner;
	InputScanner();
	virtual ~InputScanner();
	static void* readUserInput(void* instance);

private:
	void pushButton();
	void tripIR();
	void motorOverCurrent();
};

#endif /* INPUTSCANNER_H_ */
