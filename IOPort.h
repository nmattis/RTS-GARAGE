/*
 * IOPort.h
 *
 *  Created on: Mar 7, 2018
 *      Author: nxm5757
 */

#ifndef IOPORT_H_
#define IOPORT_H_

#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#define IO_PORT_SIZE 1
#define PORT_A_ON (16)
#define PORT_B_OFF (253)
#define CTRL_ADDRESS (0x28B)
#define PORT_A_ADDRESS (0x288)
#define PORT_B_ADDRESS (0x289)


class IOPort {
public:
	IOPort();
	virtual ~IOPort();
	uintptr_t ctrl_handle;
	uintptr_t port_b_output;
	uintptr_t port_a_input;

};

#endif /* IOPORT_H_ */
