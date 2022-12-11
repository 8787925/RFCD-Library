/*
 * Sensor.h
 *
 *  Created on: Oct 29, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_SENSOR_H_
#define FOUNDATION_SENSOR_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Listener.h"

template <class realtype, class readingType>

class Sensor
{
public:
	//
	//Sensor()
	//

	Sensor()
	{
		storedReading_ = 0;
		storedReading_ = storedReading_-1;
		gain_ = 1;
		offset_ = 0;
	};


	//
	//setGain(realtype)
	//

	void setGain(realtype gain)
	{
		gain_ = gain;
	}

	realtype getGain()
	{
		return gain_;
	}


	//
	//setOffset(realtype)
	//

	void setOffset(realtype offset)
	{
		offset_ = offset;
	}

	realtype getOffset()
	{
		return offset_;
	}


	//
	//getReading()
	//

	realtype getReading()
	{
		return (gain_ * this->readRaw()) + offset_;
	}


	//
	//readRaw()
	//

	virtual readingType readRaw() = 0;


	//
	//insertReading(uint16_t)
	//

	void insertReading(readingType newReading)
	{
		storedReading_ = newReading;
	};


	//
	//enable(bool)
	//

	virtual void enable() = 0;


	//
	//disable()
	//

	virtual void disable() = 0;


	//
	//remove()
	//

	virtual void remove() = 0;


	//
	//getStatus()
	//

	virtual bool getStatus() = 0;

protected:
	//
	//variables
	//

	realtype gain_;
	realtype offset_;
	readingType storedReading_;
};


#endif /* FOUNDATION_SENSOR_H_ */
