/*
 * IOPort.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: nxm5757
 */

#include "IOPort.h"

IOPort* IOPort::instance = 0;

IOPort* IOPort::getInstance() {
	if (instance == 0) {
		instance = new IOPort::IOPort();
	}

	return instance;
}

IOPort::IOPort() {
	ctrl_handle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);

	if(ctrl_handle == MAP_DEVICE_FAILED) {
		perror("Failed to map control register");
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

IOPort::~IOPort() {}

void IOPort::setOutputPinOn(int pin) {
	uint8_t port_val = this->readPort(PORT_B);
	uint8_t set_val = (port_val | pin);
	out8(this->port_b_output, set_val);
}

void IOPort::setOutputPinOff(int pin) {
	uint8_t port_val = this->readPort(PORT_B);
	uint8_t set_val = (port_val & (~pin));
	out8(this->port_b_output, set_val);
}

uint8_t IOPort::readPort(char port) {
	switch(port) {
		case 'A':
			return in8(this->port_a_input);
		case 'B':
			return in8(this->port_b_output);
		default:
			uint8_t nothing = 0;
			return nothing;
	}
}
