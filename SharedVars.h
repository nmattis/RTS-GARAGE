/*
 * SharedVars.h
 *
 *  Created on: Feb 24, 2018
 *      Author: nxm5757
 */

#ifndef SHAREDVARS_H_
#define SHAREDVARS_H_

#include <pthread.h>

#define UP (1)
#define DOWN (0)
#define ON (1)
#define OFF (0)

enum InputEvents {
	RemoteButton = 0,
	IRSensor = 1,
	MotorOC = 2,
	FullOpen = 3,
	FullClose = 4,
	None = 3
};

extern InputEvents INPUT;

extern bool DIRECTION;
extern bool SHOULD_MOVE;
extern bool IR_SENSOR;

extern int MOTOR_POS;

extern bool FULL_OPEN;
extern bool FULL_CLOSE;

extern pthread_mutex_t inputScannerMutex;

#endif /* SHAREDVARS_H_ */
