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
#define CTRL_ADDRESS 0x28B

class IOPort {
public:
	IOPort();
	virtual ~IOPort();
	uintptr_t ctrlHandle;

};

#endif /* IOPORT_H_ */
