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
namespace asio = boost::asio;

class SerialInterface {
public:
	SerialInterface(std::string end_point, int baud_rate = 2400);
	~SerialInterface();

public:
	int ReadBlock(const char *start = "/", const char *end = "\\");
	char* GetData() { return data_buff_; }

public:
	int ReadInterface();

protected:
	std::string end_point_;
    asio::io_service io_;
    asio::serial_port port_;
	char read_buff_[11];
	char data_buff_[256];
	int data_len_;
	bool read_buff_valid_;
};

#endif /* SERIAL_INTERFACE_H_ */
