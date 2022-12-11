/*
 * Sensor.h
 *
 *  Created on: Jun 18, 2015
 *      Author: Jimmy
 */

#ifndef APPLICATION_SENSOR_H_
#define APPLICATION_SENSOR_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC.h> //TODO this should be the requesting object's type/include ex:spi/can/adc

class Sensor: private ADC_Sensor{
public:
	//
	//constructor(float,float, SensorList)
	//
	//constructor asking gain, offset and sensor pointer

	Sensor(float Gain, float Offset, SensorList SensorObject);


	//
	//currentValue()
	//
	//returns the stored value of the sensor object

	float currentValue();
	uint16_t currentIntValue(); 


	//
	//current_dT()
	//
	//returns the stored dT of the sensor object

	uSeconds current_dT();


	//
	//newValue()
	//
	//returns after retrieving a new reading of the variable, if possible (for polling type)

	float newValue();


	//
	//currentLongClock();
	//
	//returns the reading's clock value

	uSeconds currentLongClock();
};


#endif /* APPLICATION_SENSOR_H_ */
