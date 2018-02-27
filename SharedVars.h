/*
 * SharedVars.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef SHAREDVARS_H_
#define SHAREDVARS_H_

#include <pthread.h>

#define UP (true)
#define DOWN (false)
#define ON (true)
#define OFF (false)

enum InputEvents {
	RemoteButton = 0,
	IRSensor = 1,
	MotorOC = 2,
	FullOpen = 3,
	FullClose = 4,
	None = 5
};

extern InputEvents INPUT;

extern bool DIRECTION;
extern bool SHOULD_MOVE;
extern bool IR_SENSOR;

extern int MOTOR_POS;

extern bool FULL_OPEN;
extern bool FULL_CLOSE;

extern pthread_mutex_t MUTEX;

#endif /* SHAREDVARS_H_ */
