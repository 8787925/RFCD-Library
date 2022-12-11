/*
 * DACObject.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Jimmy
 */


	//
	//constructor(adcList)
	//

	DACObject::DACObject(dacList OutputObject){

	}

	//
	//updateOutput(float)
	//
	//updates the output with the handed value (signal conditioning is to saturate at high and low)

	void DACObject::setOutput(float Value){

	}
	void DACObject::setOutput(uint16_t Value){

	}


	//
	//updateDutyCycle(float)
	//
	//updates the output, adjusted by percent

	void DACObject::setDutyCycle(float Percent){

	}
	void DACObject::setDutyCycle(uint16_t fiftyMiliPercent){

	}


	//
	//uint16_t getOutput()
	//
	//returns the COMPARE value of the output device, or the bit value of the ADC

	uint16_t DACObject::getOutput(){

	}


	//
	//float getFloatDutyCycle()
	//
	//returns the percent duty cycle (or percent to maximum) of the device

	float DACObject::getFloatDutyCycle(){

	}


	//
	//uint16_t getIntDutyCycle()
	//
	//returns the percent duty cycle (or percent to maximum of the device (0.05% per bit)

	uint16_t DACObject::getIntDutyCycle(){

	}

	//
	//localUpdate(dacList)
	//
	//virtual method to placehold for the update routine of the actual object

	virtual void DACObject::localUpdate(dacList Object){

	}


	//
	//localgetOutput(dacList)
	//
	//virtual method to placehold for the getoutput routine of the actual object

	virtual uint16_t DACObject::localgetOutput(dacList Object){

	}

