/*
 * ADC.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: Jimmy
 */

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC.h>

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC_Devices.h>
#include <math.h>

//
//Constructor(SensorList)
//

ADC_Sensor::ADC_Sensor(SensorList ADCobj, float SensorGain, float SensorOffset){
	localReading.SensorGain = SensorGain;
	localReading.SensorOffset = SensorOffset;
	localADCobj = ADCobj;
	localReading.TimeStamp.Running = true;
	
	this->Reactivate();
}


//
//intValue()
//

int16_t ADC_Sensor::intValue(){
	return int16_t(localReading.Sensor_Float);
}


//
//Value()
//

float ADC_Sensor::Value(){
	return localReading.Sensor_Float;
}


//
//getGain()
//

float ADC_Sensor::getGain(){
	return localReading.SensorGain;
}


//
//setGain(float)
//

void ADC_Sensor::setGain(float newGain){
	localReading.SensorGain = newGain;
}


//
//setGain(int16_t)
//

void ADC_Sensor::setGain(int16_t newGain){
	localReading.SensorGain = float(newGain);
}


//
//getOffset()
//

float ADC_Sensor::getOffset(){
	return localReading.SensorOffset;
}
//
//setOffset(float)
//

void ADC_Sensor::setOffset(float newOffset){
	localReading.SensorOffset = newOffset;
}


//
//setOffset(int16_t)
//

void ADC_Sensor::setOffset(int16_t newOffset){
	localReading.SensorOffset = float(newOffset);
}


//
//Raw()
//

uint16_t ADC_Sensor::Raw(){
	return localReading.ADC_Raw;
}


//
//get_dT()
//

uSeconds ADC_Sensor::get_dT(){
	return this->dT(localReading.TimeStamp);
}


//
//getLongClock()
//

uSeconds ADC_Sensor::get_LongClock(){
	return localReading.TimeStamp.LongClockStamp;
}


//
//ReadNew()
//

void ADC_Sensor::ReadNew(){
	this->UpdateTime(localReading.TimeStamp);
	//localReading.TimeStamp.LongClockStamp = 22;
	//localReading.TimeStamp.T_One = 21;
	localReading.ADC_Raw = ADC_Devices::instance()->readNew(localADCobj);
	this->makeADCFloat();
}


//
//Deactivate()
//

void ADC_Sensor::Deactivate(){
	ADC_Devices::instance()->clearCurrent(localADCobj);
}


//
//Reactivate()
//

void ADC_Sensor::Reactivate(){
	ADC_Devices::instance()->setupNew(localADCobj);
}


//
//makeADCFloat()
//

void ADC_Sensor::makeADCFloat(){

	localReading.Sensor_Float = float(fma(double(localReading.SensorGain),double(localReading.ADC_Raw),double(localReading.SensorOffset)));

}
