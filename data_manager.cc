/*
 * data_manager.cc
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#include "data_manager.h"

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

void DataManager::AddJSONKey(std::string key) {
	if (json_data_.length() > 2) json_data_.append(",");
	json_data_.append("\n\t\"");
	json_data_.append(key);
	json_data_.append("\": ");
}

void DataManager::AddToJSON(std::string key, std::string value) {
	AddJSONKey(key);
	json_data_.append("\"");
	json_data_.append(value);
	json_data_.append("\"");
}

void DataManager::AddToJSON(std::string key, bool value) {
	AddJSONKey(key);
	if (value)
		json_data_.append("true");
	else
		json_data_.append("false");
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
	AddToJSON(key, value);
	*ptr = end;
	return 0;
}

int DataManager::ReadRecord() {
	if (!interface_) return -1;
	if (interface_->ReadBlock() == 0) return -1;
	try {
		char *data = interface_->GetData();

		/* Lock the JSON variable and update. */
		boost::lock_guard<boost::mutex> lock(json_data_mutex_);
		json_data_.clear();
		json_data_.append("{");

		/* Read until the stream is over or an error. */
		while ((ReadTupple(&data) == 0) && (data));
		if (data) {
			AddToJSON("VALID", false);
		} else {
			AddToJSON("VALID", true);
		}
		json_data_.append("\n}");
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

