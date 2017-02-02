/*
 * SerialDevice.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_SERIALDEVICE_H_
#define FOUNDATION_SERIALDEVICE_H_

template <const uint8_t BUFFERLENGTH>

class SerialDevice: public FifoPointerBuffer <DataRequest, BUFFERLENGTH>
{
public:
	//
	//constructor
	//

	SerialDevice()
	{
		enabled_ = false;
		transmitting_ = false;
		recieving_ = false;
	}


	//
	//startStream(ByteRequest*)
	//

	virtual void startStream(DataRequest* byteRequest)
	{
		this->add(byteRequest); //serialio device driver is to include this class and have a real methodm,,,
		this->beginTransmission();
	}


	//
	//finishedStream(ByteRequest*)
	//

	virtual void finishedStream(DataRequest* byteRequest)
	{
		this->remove(byteRequest);
	}


	//
	//isBusy()
	//

	virtual bool isBusy()
	{
		return
	}


	//
	//beginTransimission()
	//

	virtual void beginTransmission() = 0;

	//
	//status()
	//

	virtual bool status()
	{
		return enabled_;
	}


	//
	//enable()
	//

	virtual void enable()
	{
		enabled_ = true;
	}


	//
	//disable()
	//

	virtual void disable()
	{
		enabled_ = false;
	}

private:

	//
	//variables
	//

	bool transmitting_;
	bool recieving_;
	bool enabled_;

};


#endif /* FOUNDATION_SERIALDEVICE_H_ */
