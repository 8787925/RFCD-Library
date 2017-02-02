/*
 * SensorGain.h
 *
 *  Created on: Nov 17, 2016
 *      Author: Jimmy
 */

#ifndef HARDWARE_SENSORGAIN_H_
#define HARDWARE_SENSORGAIN_H_


template <class ReadingType, class ReturnType>

class SensorGain
{
	//
	//constructor
	//

	SensorGain(ReturnType Gain, ReturnType Offset)
	{
		gain_ = Gain;
		offset_ = Offset;
	};


	//
	//setGain(ReturnType)
	//

	void setGain(ReturnType Gain)
	{
		gain_ = Gain;
	}


	//
	//setOffset(ReturnType)
	//

	void setOffset(ReturnType Offset)
	{
		offset_ = Offset;
	}


	//
	//transfer(ReadingType)
	//

	ReturnType transfer(ReadingType value)
	{
		return (ReturnType(value)*gain_) + offset_;
	}


private:
	//
	//variables
	//

	ReturnType gain_;
	ReturnType offset_;
};


#endif /* HARDWARE_SENSORGAIN_H_ */
