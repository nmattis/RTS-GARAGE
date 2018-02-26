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
		if (lastShouldMoveState != ::SHOULD_MOVE) {
			if (::SHOULD_MOVE == true) {
				std::cout << "Motor on!" << std::endl;
			} else {
				std::cout << "Motor off!" << std::endl;
			}
		}
		if (::SHOULD_MOVE) {
			((Motor*)instance)->motorMove(::DIRECTION);
			usleep(1000000);
		}

		lastShouldMoveState = ::SHOULD_MOVE;
		usleep(1000000);
	}

	return 0;
}

void Motor::motorMove(bool direction) {
	switch(::MOTOR_POS) {
		case 10:
			std::cout << std::endl << "Should be open." << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::INPUT = FullOpen;
			pthread_mutex_unlock( &::MUTEX );
			break;
		case 0:
			std::cout << std::endl << "Should be closed." << std::endl;
			pthread_mutex_lock( &::MUTEX );
			::INPUT = FullClose;
			pthread_mutex_unlock( &::MUTEX );
			break;
		default:
			if (direction) {
				std::cout << std::endl << "Motorpos = " << ::MOTOR_POS << std::endl;
				pthread_mutex_lock( &::MUTEX );
				::MOTOR_POS++;
				pthread_mutex_unlock( &::MUTEX );
			} else {
				std::cout << std::endl << "Motorpos = " << ::MOTOR_POS << std::endl;
				pthread_mutex_lock( &::MUTEX );
				::MOTOR_POS--;
				pthread_mutex_unlock( &::MUTEX );
			}
	}
}

