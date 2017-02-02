/*
 * PID.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: Jimmy
 */

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\PID.h>


//
//Constructor(float, float, float, ADC_Sensor&)
//

PID::PID(float P, float I, float D, Sensor& SensorDevice){
	localSensor = &SensorDevice;
	hasSensor_ = true;
	localPgain = P;
	localIgain = I;
	localDgain = D;
	localUpperLimit = INFINITY; //max
	localLowerLimit = -INFINITY; //min
	X_zero = 0;
	Ivalue = 0;
	Pvalue = 0;
	Dvalue = 0;
	localError = 0;
}

PID::PID(float P, float I, float D, Sensor& SensorDevice, float UpperSaturation, float LowerSaturation){
	localSensor = &SensorDevice;
	hasSensor_ = true;
	localPgain = P;
	localIgain = I;
	localDgain = D;
	localUpperLimit = UpperSaturation;
	localLowerLimit = LowerSaturation;
	X_zero = 0;
	Ivalue = 0;
	Pvalue = 0;
	Dvalue = 0;
	localError = 0;
	localSensor->newValue();
}


//
//updateLoop(float)
//

float PID::updateLoop(float Setpoint){

	localError = Setpoint - localSensor->newValue();

	if (localDgain==0){ //PI LOOP

		if (localIgain==0){ // P LOOP
			return (localPgain*localError);
		}

		Ivalue += (localError * float(localSensor->current_dT()))/float(1000000);
		
		if (Ivalue>localUpperLimit){Ivalue=localUpperLimit;}
		if (Ivalue<localLowerLimit){Ivalue=localLowerLimit;}
		return (localPgain*localError)+(localIgain*Ivalue);
	}

	Dvalue = (localError - X_zero)/float(localSensor->current_dT()/1000000);
	X_zero = localError;
	return (localPgain*localError)+(localIgain*Ivalue)+(localDgain*Dvalue); //FULL PID LOOP
}

//
//setIgain(float)
//

void PID::setIgain(float newGain){
	localIgain = newGain;
}


//
//setPgain(float)
//

void PID::setPgain(float newGain){
	localPgain = newGain;
}


//
//setDgain(float)
//

void PID::setDgain(float newGain){
	localDgain = newGain;
}


//
//setSaturationLower(float)
//

void PID::setSaturationLower(float LowerLimit){
	localLowerLimit = LowerLimit;
}


//
//setSaturationUpper(float)
//

void PID::setSaturationUpper(float UpperLimit){
	localUpperLimit = UpperLimit;
}


//
//getPvalue()
//

float PID::getPvalue(){
	return (localPgain*localError);
}


//
//getError()
//

float PID::getError(){
	return localError;
}

