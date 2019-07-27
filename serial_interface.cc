/*
 * serial_interface.cc
 *
 *  Created on: 27/07/2019
 *      Author: Ajo Robert
 */

#include "serial_interface.h"
#include <iostream>

SerialInterface::SerialInterface(std::string end_point, int baud_rate):
					end_point_(end_point), port_(io_),
					read_len_ (0), data_len_ (0),
					read_buff_valid_(false) {
	std::cout << "Opening port: " << end_point << std::endl;

	/* Configure the serial interface for reading. */
	port_.open(end_point.c_str());
    port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    port_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
    port_.set_option(asio::serial_port_base::character_size(8));
    port_.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
    port_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
}

SerialInterface::~SerialInterface() {
	port_.close();
}

int SerialInterface::ReadInterface() {
	int len = asio::read(port_, asio::buffer(read_buff_, sizeof(read_buff_) - 1));
	read_buff_[len] = 0;
	return len;
}

int SerialInterface::ReadBlock(const char *start, const char *end) {
	data_len_ = 0;
	char *start_ptr = NULL;
	/* Check for start element, continue read if not found. */
	if (read_buff_valid_)
		start_ptr = std::strstr(read_buff_, start);
	while (!start_ptr) {
		read_len_ = ReadInterface();
		start_ptr = std::strstr(read_buff_, start);
	}
	++start_ptr;

	/* Copy block data available in this packet. */
	int len = read_len_ - (start_ptr - read_buff_);
	std::memcpy(data_buff_, start_ptr, len);
	data_len_ += len;

	/* Read until end element appears. */
	char *end_ptr = NULL;
	while (!end_ptr) {
		read_len_ = ReadInterface();
		end_ptr = std::strstr(read_buff_, end);
		if (end_ptr) {
			break;
		}
		std::memcpy(data_buff_ + data_len_, read_buff_, read_len_);
		data_len_ += read_len_;
	}

	/* Read till the end element in the last read buffer. */
	len = end_ptr - read_buff_;
	std::memcpy(data_buff_ + data_len_, read_buff_, len);
	data_len_ += len;
	data_buff_[data_len_] = 0;
	read_buff_valid_ = true;
	return data_len_;
}
