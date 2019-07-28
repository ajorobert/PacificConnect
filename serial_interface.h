/*
 * serial_interface.h
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#ifndef SERIAL_INTERFACE_H_
#define SERIAL_INTERFACE_H_

#include <string>
#include <vector>
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include "device_interface.h"

namespace asio = boost::asio;

class SerialInterface: public DeviceInterface {
public:
	SerialInterface(std::string end_point, int baud_rate = 2400);
	~SerialInterface();

public:
	/*
	 * Read a block of data from the given serial interface.
	 *
	 * @param	start	Delimiter string to identify start of block.
	 * @param	end		Delimiter string to identify end of block.
	 *
	 * @return	No of bytes read as a block.
	 */
	int ReadBlock(const char *start = "/", const char *end = "\\");

protected:
	/*
	 * Performs low level read from the open interface handle.
	 *
	 * @return	Bytes read.
	 */
	int ReadInterface();

protected:
	std::string end_point_;
    asio::io_service io_;
    asio::serial_port port_;
	char read_buff_[11];
	int read_len_;
	bool read_buff_valid_;
};

#endif /* SERIAL_INTERFACE_H_ */
