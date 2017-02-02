/*
 * AnalogInput.h
 *
 *  Created on: Nov 15, 2016
 *      Author: Jimmy
 */

#ifndef HARDWARE_ANALOGINPUT_H_
#define HARDWARE_ANALOGINPUT_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Thread.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Sensor.h"

template <class SensorGainType, class SensorType, class ReadingType, class ReturnType>

class AnalogInput: public Thread
{public:
	//
	//constructor
	//

	AnalogInput(SensorType* Input, SensorGainType* Gain)
	{
		sensor_ = Input;
		gain_ = Gain;
		reading_ = 0;
		reading_ --;
	}


	//
	//update
	//

	ReturnType update()
	{	ReadingType reading;
		reading =  ReadingType(sensor_->readRaw());
		reading_ = gain_->transfer(reading);
		return reading_;
	};


	//
	//disable()
	//

	void disable()
	{
		sensor_->disable();
	}


	//
	//enable();
	//

	void enable()
	{
		sensor_->enable();
	}


	//
	//insertValue(ReturnType)
	//

	void insertValue(ReturnType value)
	{
		reading_ = value;
	}


	//
	//assignSensor(Sensor*)
	//

	void assignSensor(SensorType * Input)
	{
		sensor_ = Input;
	};
	
	
	//
	//getValue()
	//
	
	ReadingType getReading()
	{
		return reading_;
	}
	
	
	//
	//run()
	//
	
	void run()
	{
		this->insertValue(this->update());
	}


private:
	//
	//variables
	//

	SensorType* sensor_;
	SensorGainType* gain_;
	ReturnType reading_;
};



#endif /* HARDWARE_ANALOGINPUT_H_ */
