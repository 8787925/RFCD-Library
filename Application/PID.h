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

struct PIDDataTable{
	float P;
	float I;
	float D;
	float UpperSaturation;
	float LowerSaturation;
	float initialIntegrator;
};

class PID: private Timer{
public:
	//
	//constructor (float P, float I, float d)
	//

	PID(float P, float I, float D);

	PID(float P, float I, float D, float UpperSaturation, float LowerSaturation);

	PID(float P, float I, float D, float UpperSaturation, float LowerSaturation,
	    float initialSensor, float initialIntegrator);

	PID(PIDDataTable PIDdata);


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
	float getPgain(){return localPgain;};


	//
	//setIgain(float)
	//
	//sets the I term gain

	void setIgain(float newGain);
	float getIgain(){return localIgain;};


	//
	//setDgain(float)
	//
	//sets the D term gain

	void setDgain(float newGain);
	float getDgain(){return localDgain;};


	//
	//updateLoop(float Setpoint)
	//
	//runs the PID and results the new command

	float updateLoop(float Setpoint, uSeconds dt, float SensorReading);


	//
	//setSaturationUpper(int16_t)
	//
	//sets the upper saturation limit (initialized to MAX)

	void setSaturationUpper(float UpperLimit);
	float getSaturationUpper(){return localUpperLimit;};


	//
	//setSaturationlower(int16_t)
	//
	//sets the lower saturation limit (initialized to MIN)

	void setSaturationLower(float LowerLimit);
	float getSaturationLower(){return localLowerLimit;};


	//
	//intialConditions()
	//
	//runs the First sensor aq and starts the timer or sets all the intial conditions

virtual void initialConditions(float initialSensor, float initialIntegrator){
	X_zero=initialSensor;
	Ivalue=initialIntegrator;
	};

private:
	float localPgain;
	float localIgain;
	float localDgain;
	float Pvalue;
	float Ivalue;
	float Dvalue;
	float X_zero;
	float localError;
	float localUpperLimit;
	float localLowerLimit;

};



#endif /* APPLICATION_PID_H_ */
