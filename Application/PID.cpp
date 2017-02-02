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

PID::PID(float P, float I, float D){
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

PID::PID(float P, float I, float D, float UpperSaturation, float LowerSaturation){
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
	this->initialConditions(0,0); //construct assuming zero initial conditions
}


PID::PID(float P, float I, float D, float UpperSaturation, float LowerSaturation,
		 float initialSensor, float initialIntegrator){
	localPgain = P;
	localIgain = I;
	localDgain = D;
	localUpperLimit = UpperSaturation;
	localLowerLimit = LowerSaturation;
	X_zero = initialSensor;
	Ivalue = initialIntegrator;
	Pvalue = 0;
	Dvalue = 0;
	localError = 0;
}


//
//updateLoop(float, uSeconds, float)
//

float PID::updateLoop(float Setpoint, uSeconds dt, float SensorReading){

	float f_dt = float(dt)/float(uSECONDS_PER_SECOND); //convert the dt into a real seconds

	localError = Setpoint - SensorReading;

	if (localDgain!=0){//perform D mathematics
		Dvalue = (localError-X_zero)/f_dt; //(X1 - X0)/dt
		X_zero = localError; //update for next loop's X0 to be this loop's X1
	}
	else{
		Dvalue = 0;//Make sure that if there has been an alteration to gains, it's reflected
	}

	if (localPgain != 0){//perform P mathematics
		Pvalue = localPgain*localError;
	}
	else{
		Pvalue = 0; //Make sure that if there's been an alteration to gains, it's reflected
	}

	if (localIgain != 0){//perform I mathematics
		Ivalue += localIgain * (localError * f_dt); // I =I_0 + gain*Error*(dt))
		if (Ivalue>localUpperLimit){Ivalue=localUpperLimit;} //Check for upper saturation of I value
		if (Ivalue<localLowerLimit){Ivalue=localLowerLimit;} //check for lower saturation of I value
	}
	else{
		Ivalue = 0; //Make sure that if there's been an alteration to gains, it's reflected
	}


	return (Pvalue)+(Ivalue)+(Dvalue); //return the sum of PID terms
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
	return (Pvalue);
}


//
//getIvalue()
//

float PID::getIvalue(){
	return (Ivalue);
}


//
//getDvalue()
//

float PID::getDvalue(){
	return (Dvalue);
}


//
//getError()
//

float PID::getError(){
	return localError;
}

