/*
 * ADC.h
 *
 *  Created on: Jun 15, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_ADC_H_
#define HARDWARE_ADC_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\LongClock.h>

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADCDevicesList.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC_Devices.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Timer.h>
#include <stdint.h>

struct ADC_Reading{
	Time TimeStamp;
	uint16_t ADC_Raw;
	float Sensor_Float;
	float SensorGain;
	float SensorOffset;
};

class ADC_Sensor: private Timer{
public:

	//
	//uint16_t Raw()
	//
	//returns the raw value of the sensor

	uint16_t Raw();


	//
	//float Value();
	//
	//returns the real value of the sensor reading

	float Value();


	//
	//int16_t intValue();
	//
	//returns the integer value of the float (the rounded integer of the float)

	int16_t intValue();


	//
	//setGain(int16_t)
	//
	//sets the gain of the sensor

	void setGain(int16_t newGain);

	void setGain(float newGain);


	//
	//float getGain();
	//
	//returns the stored Gain value

	float getGain();

	//
	//setOffset(int16_t)
	//
	//sets the offset of the sensor

	void setOffset(int16_t newOffset);

	void setOffset(float newOffset);


	//
	//float getOffset()
	//
	//returns the stored Offset value

	float getOffset();


	//
	//ReadNew()
	//
	//updates the sensor reading and timestamps

	void ReadNew();


	//
	//uSeconds get_dT()
	//
	//returns the time, in microseconds, between this reading (stored) and the previous

	uSeconds get_dT();


	//
	//uSeconds get_LongClock()
	//
	//returns the time, in microseconds, that the sensor reading was captured

	uSeconds get_LongClock();


	//
	//void Reactivate()
	//

	void Reactivate();


	//
	//void Deactivate()
	//

	void Deactivate();


	//
	//Constructor(SensorList)
	//

	ADC_Sensor(SensorList ADCobj, float SensorGain, float SensorOffset);

private:

	//
	//void unload(SensorList)
	//
	//private to remove this function and free the ADC

	void unload(SensorList adcName);


	//
	//void makeADCFloat()
	//
	//creates the sensor's float result from the ADC,Gain and Offset

	void makeADCFloat();

	SensorList localADCobj;
	ADC_Reading localReading;
};

#endif /* HARDWARE_ADC_H_ */
