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
#define	TIMER_DRIFT_CORRECTION_LOOP 6

void DisplayTimer() {
	boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
	int counter = TIMER_DRIFT_CORRECTION_LOOP;

	/* Findout the time needed to hit a 10 Second boundary. */
	int remaining = 10 - (timeLocal.time_of_day().seconds() % 10);
	sleep (remaining);
	while (1) {
		manager->PrintRecord();
		--counter;
		if (counter == 0) {
			/* Adjust the timer. */
			boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
			/* Findout the time needed to hit a 10 Second boundary. */
			remaining = 10 - (timeLocal.time_of_day().seconds() % 10);
			counter = TIMER_DRIFT_CORRECTION_LOOP;
		} else {
			/* Assume we are at 10 second boundary and sleep for another 10s. */
			remaining = 10;
		}
		sleep (remaining);
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

	boost::thread timer = boost::thread(DisplayTimer);
	while (manager->ReadRecord() == 0) {
		//manager->PrintRecord();
	}
	timer.join();

	return 0;
}

