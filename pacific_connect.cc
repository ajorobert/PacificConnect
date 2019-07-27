/*
 * pacific_connect.cc
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#include <iostream>
#include "serial_interface.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Invalid use of the application. Please specify the serial interface as an argument." << std::endl;
	}
	SerialInterface serial(argv[1]);
	while (1) {
		serial.ReadBlock();
	}
	return 0;
}


