/*
 * GenericSensorHardware.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Jimmy
 */

#ifndef HARDWARE_GENERICSENSORHARDWARE_H_
#define HARDWARE_GENERICSENSORHARDWARE_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Sensor.h"

template <class realtype, class readingtype>

class GenericSensor: private Sensor<realtype, readingtype>
{
public:
	//
	//instance()
	//

	GenericSensor* instance()
	{
		static GenericSensor theGenericSensor;
		return &theGenericSensor;
	}


	//
	//getStatus()
	//

	bool getStatus()
	{
		return enabled_;
	}


	//
	//enable()
	//

	void enable()
	{
		//code concerning hardware enable of the sensor
		enabled_ = true;
	}


	//
	//disable()
	//

	void disable()
	{
		//code concerning hardware disable of the sensor
		enabled_ = false;
	}


	//
	//remove()
	//

	void remove()
	{
		//code concerning removal and disabling of the hardware from the system.
	}


	//
	//readRaw()
	//

	readingtype readRaw()
	{
		readingtype temp;

		//code concerning the hardware method for getting raw bits

		this->storedReading_ = temp;
		return temp;
	}


private:
	//
	//constructor
	//

	GenericSensor()
	{
		//lastRealReading_ = 0;
		enabled_=false;
	}


	//
	//variables
	//

	//realtype lastRealReading_;
	bool enabled_ = false;
};


#endif /* HARDWARE_GENERICSENSORHARDWARE_H_ */
