/*
 * PID.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Jimmy
 */

#ifndef APPLICATION_PID_H_
#define APPLICATION_PID_H_

#include <math.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Timer.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\Sensor.h>

class PID: private Timer{
public:
	//
	//constructor (float P, float I, float d, ADC_Sensor&)
	//

	PID(float P, float I, float D, Sensor& SensorDevice);
	PID(float P, float I, float D, Sensor& SensorDevice, float UpperSaturation, float LowerSaturation);


	//
	//getError()
	//
	//returns difference between error and command

	float getError();


	//
	//getP()
	//
	//returns the P term contribution to the output

	float getPvalue();


	//
	//getI()
	//
	//returns the I contribution to the output

	float getIvalue();


	//
	//getD()
	//
	//returns the D contribution to the output

	float getDvalue();


	//
	//setPgain(float);
	//
	//sets the P term gain

	void setPgain(float newGain);


	//
	//setIgain(float)
	//
	//sets the I term gain

	void setIgain(float newGain);


	//
	//setDgain(float)
	//
	//sets the D term gain

	void setDgain(float newGain);


	//
	//updateLoop(float Setpoint)
	//
	//runs the PID and results the new command

	float updateLoop(float Setpoint);


	//
	//setSaturationUpper(int16_t)
	//
	//sets the upper saturation limit (initialized to MAX)

	void setSaturationUpper(float UpperLimit);


	//
	//setSaturationlower(int16_t)
	//
	//sets the lower saturation limit (initialized to MIN)

	void setSaturationLower(float LowerLimit);

private:
	Sensor* localSensor;
	float localPgain;
	float localIgain;
	float localDgain;
	float Ivalue;
	float X_zero;
	float Pvalue;
	float Dvalue;
	float localError;
	int16_t localUpperLimit;
	int16_t localLowerLimit;
	bool hasSensor_;

};



#endif /* APPLICATION_PID_H_ */
