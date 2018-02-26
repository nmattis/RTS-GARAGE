/*
 * Motor.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
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
