/*
 * IOPort.h
 */

#ifndef IOPORT_H_
#define IOPORT_H_

#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <stdio.h>

/**
 * Port A, B, CTRL addresses of the registers
 * Port A is our Input so ON value to reflect that
 * Port B is our Output so OFF value to reflect that
 *
 * Port A, B character defines
 * Register Bit definitions for readablity
 */
#define IO_PORT_SIZE 1
#define PORT_A_ON (16)
#define PORT_B_OFF (253)
#define CTRL_ADDRESS (0x28B)
#define PORT_A_ADDRESS (0x288)
#define PORT_B_ADDRESS (0x289)
#define PORT_A 'A'
#define PORT_B 'B'
#define REST_PIN (8)
#define BIT0 (0x1)
#define BIT1 (0x2)
#define BIT2 (0x4)
#define BIT3 (0x8)
#define BIT4 (0x10)


class IOPort {
public:
	static IOPort* getInstance();

	void setOutputPinOn(int pin);
	void setOutputPinOff(int pin);
	uint8_t readPort(char port);
private:
	static IOPort* instance;
	uintptr_t ctrl_handle;
	uintptr_t port_b_output;
	uintptr_t port_a_input;
	IOPort();
	virtual ~IOPort();
};

#endif /* IOPORT_H_ */
