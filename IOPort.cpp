/*
 * IOPort.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: nxm5757
 */

#include "IOPort.h"

IOPort::IOPort() {
	// TODO Auto-generated constructor stub
	ctrlHandle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);
	if(ctrlHandle == MAP_DEVICE_FAILED) {
		perror("Failed to map control register");
		exit();
	}
	// Port A input, Port B output
	uint8_t ctrl_port_value = in8(ctrlHandle);
	ctrl_port_value |= PORT_A_ON;
	ctrl_port_value &= PORT_B_OFF;
	out8( ctrlHandle, ctrl_port_value );
}



IOPort::~IOPort() {
	// TODO Auto-generated destructor stub
}
