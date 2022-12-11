/*
 * Sensor.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: Jimmy
 */

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\Sensor.h>

//
//constructor()
//

Sensor::Sensor(float Gain, float Offset, SensorList SensorObject): ADC_Sensor(SensorObject, Gain, Offset){

}


//
//currentValue()
//

float Sensor::currentValue(){
	return this->Value();
}

uint16_t Sensor::currentIntValue(){
	return this->Raw();
}


//
//newValue()
//

float Sensor::newValue(){
	this->ReadNew();
	return this->Value();
}


//
//current_dT()
//

uSeconds Sensor::current_dT(){
	return this->get_dT();
}


//
//currentLongClock()
//

uSeconds Sensor::currentLongClock(){
	return this->get_LongClock();
}
