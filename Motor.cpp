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
	pthread_create(&motor, &attr, Motor::listenToCtrl, this);
}

Motor::~Motor() {
	// TODO
}

void* Motor::listenToCtrl(void* instance) {
	bool lastShouldMoveState = ::SHOULD_MOVE;
	while(true) {
		if (lastShouldMoveState) {
			((Motor*)instance)->motorMove(::DIRECTION);
			usleep(1000000);
		}
		lastShouldMoveState = ::SHOULD_MOVE;
	}

	return 0;
}

void Motor::motorMove(bool direction) {
	//UP is 1
	if (direction) {
		if (::MOTOR_POS == 0) {
			std::cout << "Motor On!" << std::endl;
		}

		if (::MOTOR_POS < 10) {
			std::cout << std::endl << "Motorpos = " << ::MOTOR_POS << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::MOTOR_POS++;
			pthread_mutex_unlock( &::MUTEX );
		} else {
			std::cout << "Motor Off!" << std::endl;
			std::cout << std::endl << "Should be open." << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::INPUT = FullOpen;
			pthread_mutex_unlock( &::MUTEX );
		}
	} else {
		if (::MOTOR_POS == 10) {
			std::cout << "Motor On!" << std::endl;
		}

		if (::MOTOR_POS > 0) {
			std::cout << std::endl << "Motorpos = " << ::MOTOR_POS << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::MOTOR_POS--;
			pthread_mutex_unlock( &::MUTEX );
		} else {
			std::cout << "Motor Off!" << std::endl;
			std::cout << std::endl << "Should be closed." << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::INPUT = FullClose;
			pthread_mutex_unlock( &::MUTEX );
		}
	}
}

