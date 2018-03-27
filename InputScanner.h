/*
 * InputScanner.h
 *
 */

#ifndef INPUTSCANNER_H_
#define INPUTSCANNER_H_

#include <pthread.h>
#include <iostream>
#include <unistd.h>

#include "IOPort.h"
#include "SharedVars.h"

class InputScanner {
public:
	pthread_t inputScanner;
	InputScanner();
	virtual ~InputScanner();
	static void* readUserInput(void* instance);

private:
	static void pushButton();
	static void tripIR();
	static void motorOverCurrent();
};

#endif /* INPUTSCANNER_H_ */
