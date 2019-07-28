/*
 * device_interface.h
 *
 *  Created on: 28/07/2019
 *      Author: Ajo Robert
 */

#ifndef DEVICE_INTERFACE_H_
#define DEVICE_INTERFACE_H_

class DeviceInterface {
public:
	DeviceInterface(): data_len_(0) {}
	virtual ~DeviceInterface() {};

public:
	/*
	 * Read a block of data from the device interface.
	 *
	 * @param	start	Delimiter string to identify start of block.
	 * @param	end		Delimiter string to identify end of block.
	 *
	 * @return	No of bytes read as a block.
	 */
	virtual int ReadBlock(const char *start = "/", const char *end = "\\") = 0;

	/*
	 * Return the last read data block.
	 *
	 * @return	pointer to data block.
	 */
	virtual char* GetData() { return data_buff_; }

protected:
	char data_buff_[256];
	int data_len_;
};

#endif /* DEVICE_INTERFACE_H_ */
