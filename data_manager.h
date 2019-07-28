/*
 * data_manager.h
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "device_interface.h"
#include <boost/thread.hpp>

class DataManager {
public:
	DataManager(DeviceInterface *interface):
		json_data_(""), interface_(interface) {}

public:
	/*
	 * Print the last read record to stdout.
	 *
	 * @return	0 	on success
	 * @return	-1	on error
	 */
	int PrintRecord();

	/*
	 * Read a block of data and perform below set of operations.
	 *  1. Parse the input data
	 *  2. Create JSON from the result.
	 *  3. Add valid field to JSON based on above steps.0
	 *
	 * @return	0 	on success
	 * @return	-1	on error
	 */
	int ReadRecord();

protected:
	/*
	 * Consume the given char stream till start of data is reached.
	 *
	 * @param	ptr		Stream pointer.
	 *
	 * @return	Start pointer to the valid stream data.
	 */
	char* StartOfData(char *ptr);

	/*
	 * Traverse the given char stream till end of current data block.
	 *
	 * @param	ptr		Stream pointer pointing to start of data.
	 *
	 * @return	Pointer to end of valid data in the given stream.
	 */
	char* EndOfData(char *ptr);

	/*
	 * Read a next data tuple <name, value> from the given stream.
	 *
	 * @param	ptr		Stream pointer.
	 * 					Stream pointer will be updated to reflect consumed bytes on success.
	 * 					Stream pointer will be set o NULLPTR on end of stream.
	 *
	 * @return	0 	on success
	 * @return	-1	on error
	 */
	int ReadTupple(char **ptr);

	/*
	 * Add JSON key to the JSON string.
	 *
	 * @param	key		JSON Key string.
	 */
	void AddJSONKey(std::string key);

	/*
	 * Add tuple <name, value> to the JSON string.
	 *
	 * @param	key		JSON Key string.
	 * @param	value	JSON string value.
	 */
	void AddToJSON(std::string key, std::string value);

	/*
	 * Add tuple <name, value> to the JSON string.
	 *
	 * @param	key		JSON Key string.
	 * @param	value	JSON boolean value.
	 */
	void AddToJSON(std::string key, bool value);

protected:
	std::string json_data_;
	DeviceInterface *interface_;
	boost::mutex json_data_mutex_;
};

#endif /* DATA_MANAGER_H_ */
