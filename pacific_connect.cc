/*
 * pacific_connect.cc
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#include <iostream>
#include "serial_interface.h"
#include "data_manager.h"
#include <boost/thread.hpp>

static DataManager *manager;

void DisplayTimer() {
	while (1) {
		std::cout << "Printing from TImer thread." << std::endl;
		manager->PrintRecord();
		sleep(5);
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Invalid use of the application. Please specify the serial interface as an argument." << std::endl;
		return -1;
	}
	SerialInterface serial(argv[1]);
	manager = new DataManager(serial);
	if (!manager){
		std::cout << "Data manager module init failed." << std::endl;
		return -1;
	}

	//boost::thread timer = boost::thread(DisplayTimer);
	while (manager->ReadRecord() == 0) {
		manager->PrintRecord();
	}
	//timer.join();
	return 0;
}

