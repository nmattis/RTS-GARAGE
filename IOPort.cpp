/*
 * IOPort.cpp
 *
 * Singleton class for setting up the ports on the purple
 * box for input output. Also has helper functoins for
 * allowing easy manipulation of the bits of those
 * registers.
 */

#include "IOPort.h"

// singleton instance, uninitialized
IOPort* IOPort::instance = 0;

/**
 * Function to allow other classes access to the
 * singleton. If the class has not been instantiated
 * yet this function is responsible for that.
 */
IOPort* IOPort::getInstance() {
	if (instance == 0) {
		instance = new IOPort::IOPort();
	}

	return instance;
}

/**
 * Constructor, maps the registers, and sets up initially
 * the ports to be input/output.
 */
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

/** destructor */
IOPort::~IOPort() {}

/**
 * Function for setting a specific bit on PORT B to ON or 1.
 */
void IOPort::setOutputPinOn(int pin) {
	uint8_t port_val = this->readPort(PORT_B);
	uint8_t set_val = (port_val | pin);
	out8(this->port_b_output, set_val);
}

/**
 * Function for setting a specific bit on PORT B to OFF or 0.
 */
void IOPort::setOutputPinOff(int pin) {
	uint8_t port_val = this->readPort(PORT_B);
	uint8_t set_val = (port_val & (~pin));
	out8(this->port_b_output, set_val);
}

/**
 * Reads data from a specific port, in this case
 * Port A or B.
 */
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
