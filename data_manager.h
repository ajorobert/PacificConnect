/*
 * data_manager.h
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "serial_interface.h"
#include <boost/property_tree/ptree.hpp>

namespace PT = boost::property_tree;

class DataManager {
public:
	DataManager(SerialInterface &interface):
		json_data_(""), interface_(interface) {}

public:
	int PrintRecord();
	int ReadRecord();

protected:
	char* StartOfData(char *ptr);
	char* EndOfData(char *ptr);
	int ReadTupple(char **ptr);

protected:
	PT::ptree tp_data_;
	std::string json_data_;
	SerialInterface &interface_;
};

#endif /* DATA_MANAGER_H_ */
