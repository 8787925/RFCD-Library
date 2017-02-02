/*
 * DACObject.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Jimmy
 */

#ifndef APPLICATION_DACOBJECT_H_
#define APPLICATION_DACOBJECT_H_

#include <avr/io.h>

enum dacList{
	PWM1,
	PWM2,
	PWM3,
	PWM4,
	PWM5,
	PWM6,
	PWM7,
	PWM8,
	PWM9,
	DAC1,
	DAC2

};


class DACObject{

	//
	//constructor(adcList)
	//

	DACObject(dacList OutputObject);

	//
	//updateOutput(float)
	//
	//updates the output with the handed value (signal conditioning is to saturate at high and low)

	void setOutput(float Value);
	void setOutput(uint16_t Value);


	//
	//updateDutyCycle(float)
	//
	//updates the output, adjusted by percent

	void setDutyCycle(float Percent);
	void setDutyCycle(uint16_t fiftyMiliPercent);


	//
	//uint16_t getOutput()
	//
	//returns the COMPARE value of the output device, or the bit value of the ADC

	uint16_t getOutput();


	//
	//float getFloatDutyCycle()
	//
	//returns the percent duty cycle (or percent to maximum) of the device

	float getFloatDutyCycle();


	//
	//uint16_t getIntDutyCycle()
	//
	//returns the percent duty cycle (or percent to maximum of the device (0.05% per bit)

	uint16_t getIntDutyCycle();


	//
	//localUpdate(dacList)
	//
	//virtual method to placehold for the update routine of the actual object

	virtual void localUpdate(dacList Object);


	//
	//localgetOutput(dacList)
	//
	//virtual method to placehold for the getoutput routine of the actual object

	virtual uint16_t localgetOutput(dacList Object);

private:

	float floatDutycycle_;
	uint16_t intDutyCycle_;
	uint16_t intOutput_;

};



#endif /* APPLICATION_DACOBJECT_H_ */
