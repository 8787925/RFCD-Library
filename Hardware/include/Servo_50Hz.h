/*
 * Servo_50Hz.h
 *
 *  Created on: May 13, 2016
 *      Author: Jimmy
 */

#ifndef HARDWARE_SERVO_50HZ_H_
#define HARDWARE_SERVO_50HZ_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\PWM.h>
#ifndef _CONFIG_H_
	typedef uint16_t fpDegrees;
	typedef uint16_t fpPercent;
#endif



class Servo_50Hz: private PWM{

	//
	//powerOn()
	//

	void powerOn();


	//
	//powerOff()
	//

	void powerOff();


	//
	//setAngle(fpDegrees);
	//

	void setAngle(fpDegrees degreesHundreths);
	void setAngle(float angle);


	//
	//setPercent(fpPercent)
	//

	void setPercent(fpPercent percentHundreths);
	void setPercent(float percent);


	//
	//getAngle()
	//

	fpDegrees getAngle();


	//
	//getPercent()
	//

	fpPercent getPercent();


	//
	//getFullRange()
	//
	//returns degrees at 100% duty cycle when 0% = 0 degrees

	fpDegrees getFullRange();
};

#endif /* HARDWARE_SERVO_50HZ_H_ */
