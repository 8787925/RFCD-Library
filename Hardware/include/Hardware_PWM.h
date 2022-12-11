/*
 * PWM.h
 *
 *  Created on: Jun 21, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_PWM_H_
#define HARDWARE_PWM_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\DACObject.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\LongClock.h>//for timer types

class PWM{
	friend class DACObject;

	//
	//constructor()
	//
	//constructs by rounding up to the next nearest frequency possible

	PWM(dacList newPWM, uSeconds period, bool squareFrequencyPWM);
	PWM(dacList newPWM, bool squareFrequencyPWM);


	//
	//setuSecondsOn(uSeconds)
	//
	//the time the pulse is intnded to be on

	void setuSecondsOn(uSeconds onTime);


	//
	//setDutyCycle(float Cycle)
	//
	//the duty cycle intended to be on

	void setDutyCycle(float Percent);


	//
	//getPeriod()
	//
	//returns the period in microseconds of the PWM being generated

	uSeconds getPeriod();

private:
	//
	//setupPWM(dacList PWM)
	//
	// responsible for setting up the new pwm object

	void setupPWM(dacList PWM);


	//
	//localUpdate(dacList PWM);
	//
	//responsible for interacting with the DAC initializer to update the output

	void localUpdate(dacList PWM);


	//
	//setupReservation(adcList Object)
	//
	//checks out the port from the semaphore

	void genClockSetup(dacList Object);

	dacList localHardware_;
	uint8_t activePWMBitPack_;
	float uSecondsPerCount;
	uint16_t countsPerTop_;
	float localDutyCycle_;
	uSeconds localPeriod_;
	uSeconds localOnTime_;
	bool usingDutyCycle_;
	uint32_t localRegisterValue_;

};


#endif /* HARDWARE_PWM_H_ */
