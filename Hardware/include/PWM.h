/*
 * PWM.h
 *
 *  Created on: Mar 28, 2017
 *      Author: mattb
 */

#ifndef HARDWARE_PWM_H_
#define HARDWARE_PWM_H_

#include "config.h"

class PWM
{
	//
	//constructor
	//


	//
	//setuSecondsOn(uSeconds)
	//
	//the time the pulse is intended to be on

	virtual void setuSecondsOn(uSeconds onTime);
	virtual uSeconds getuSecondsOn();


	//
	//setDutyCycle(float Cycle)
	//
	//the duty cycle intended to be on

	virtual void setDutyCycle(float Percent);
	virtual float getDutyCycle();


	//
	//getPeriod()
	//
	//returns the period in microseconds of the PWM being generated

	virtual void setPeriod(uSeconds Period);
	virtual uSeconds getPeriod();


	//
	//enable()
	//

	virtual void enable();


	//
	//disable(bool)
	//

	virtual void disable(bool RestingValue);

private:
	//
	//setup()
	//

	virtual void setup();

	float dutyCycle_;
	uSeconds timeOn_;
	uSeconds period_;
};


#endif /* HARDWARE_PWM_H_ */
