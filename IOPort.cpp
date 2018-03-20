/*
 * IOPort.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: nxm5757
 */

#include "IOPort.h"

IOPort::IOPort() {
	// TODO Auto-generated constructor stub
	ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);

	if(ctrl_handle == MAP_DEVICE_FAILED) {
		perror("Failed to map control register");
		exit(0);
	}
	// Port A input, Port B output
	uint8_t ctrl_port_value = in8(ctrl_handle);
	ctrl_port_value |= PORT_A_ON;
	ctrl_port_value &= PORT_B_OFF;
	out8( ctrl_handle, ctrl_port_value );

	// READ AND WRITE
	port_a_input = mmap_device_io(IO_PORT_SIZE, PORT_A_ADDRESS);
	port_b_output = mmap_device_io(IO_PORT_SIZE, PORT_B_ADDRESS);
}



IOPort::~IOPort() {
	// TODO Auto-generated destructor stub
}
