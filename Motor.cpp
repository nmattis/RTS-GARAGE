/*
 * Motor.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#include "Motor.h"

Motor::Motor() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&motor, &attr, &Motor::listenToCtrl, this);
}

Motor::~Motor() {
	// TODO
}

void* Motor::listenToCtrl(void* instance) {
	do {
		((Motor*)instance)->motorMove(::DIRECTION);
	} while(::SHOULD_MOVE);

	return 0;
}

void Motor::motorMove(bool direction) {
	switch(::MOTOR_POS) {
		case 10:
			::FULL_OPEN = 1;
			break;
		case 0:
			::FULL_CLOSE = 1;
			break;
		default:
			if (direction) {
				::MOTOR_POS++;
			} else {
				::MOTOR_POS--;
			}
	}
}
