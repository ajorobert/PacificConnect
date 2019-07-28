/*
 * data_manager.cc
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#include "data_manager.h"
#include <boost/property_tree/json_parser.hpp>

char* DataManager::StartOfData(char *ptr) {
	if (!ptr) return NULL;
	while((*ptr) &&(isspace(*ptr) || (*ptr == ':'))) ptr++;
	if (*ptr == 0) return NULL;
	return ptr;
}

char* DataManager::EndOfData(char *ptr) {
	if (!ptr) return NULL;
	while((*ptr) && (*ptr != ':') && (*ptr != '\n')) ptr++;
	if (*ptr == 0) return NULL;
	ptr--;
	while(isspace(*ptr)) ptr--;
	ptr++;
	return ptr;
}

int DataManager::ReadTupple(char **ptr) {
	char *start = StartOfData(*ptr);
	char *end = EndOfData(start);
	if (!start || !end) {
		/* End of stream. */
		if (!start) {
			*ptr = 0;
			return 0;
		}

		/* Partial data found. */
		return -1;
	}
	std::string key(start, end - start);
	start = StartOfData(end + 1);
	end = EndOfData(start);
	/* Error on partial data. */
	if (!start || !end) return -1;
	std::string value(start, end - start);
	tp_data_.put(key, value);
	*ptr = end;
	return 0;
}

int DataManager::ReadRecord() {
	if (!interface_) return -1;

	tp_data_.clear();
	if (interface_->ReadBlock() == 0) return -1;
	try {
		char *data = interface_->GetData();

		/* Read until the stream is over or an error. */
		while ((ReadTupple(&data) == 0) && (data));
		if (data) {
			tp_data_.put("VALID", "FALSE");
		} else {
			tp_data_.put("VALID", "TRUE");
		}

		std::stringstream ss;
		PT::json_parser::write_json(ss, tp_data_);
		/* Lock the JSON variable and update. */
		boost::lock_guard<boost::mutex> lock(json_data_mutex_);
		json_data_ = ss.str();

		return 0;
	} catch (...) {
		return -1;
	}
}

int DataManager::PrintRecord() {
	/* Take lock and print the JSON value. */
	boost::lock_guard<boost::mutex> lock(json_data_mutex_);
	/* If there is no valid data, skip printing empty line. */
	if (json_data_.length() == 0) return 0;
	std::cout << json_data_ << std::endl;
	return 0;
}

