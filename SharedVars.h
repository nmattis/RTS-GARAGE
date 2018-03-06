/*
 * SharedVars.h
 *
 * Globals for simulated inputs into the Garage door System.
 */

#ifndef SHAREDVARS_H_
#define SHAREDVARS_H_

#include <pthread.h>

// aliases for clarity
#define UP (true)
#define DOWN (false)
#define ON (true)
#define OFF (false)

// events that the system can fire
enum InputEvents {
	RemoteButton = 0,
	IRSensor = 1,
	MotorOC = 2,
	FullOpen = 3,
	FullClose = 4,
	None = 5
};

extern InputEvents INPUT;    // event input

extern bool DIRECTION;		 // direction the motor should move given a state
extern bool SHOULD_MOVE;	 // if the motor should be on or off
extern bool IR_SENSOR;		 // if the IR Sensor is on or off

extern int MOTOR_POS;		 // counter for the door position

extern bool FULL_OPEN;		 // state of the door, motor_pos = 10
extern bool FULL_CLOSE;		 // state of the door, motor_pos = 0

extern pthread_mutex_t MUTEX;

#endif /* SHAREDVARS_H_ */
