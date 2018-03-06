/*
 * Motor.h
 *
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <pthread.h>
#include <unistd.h>
#include <iostream>

#include "SharedVars.h"

class Motor {
public:
	pthread_t motor;
	Motor();
	virtual ~Motor();
	static void* listenToCtrl(void* instance);

private:
	void motorMove(bool direction);
};

#endif /* MOTOR_H_ */
