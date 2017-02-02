/*
 * Servo.h
 *
 *  Created on: May 13, 2016
 *      Author: Jimmy
 */

#ifndef APPLICATION_SERVO_H_
#define APPLICATION_SERVO_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\Servo_50Hz.h>



class Servo : public Servo_50Hz{
	//
	//setPosition()
	//

	virtual void setAngle(fpDegrees degreesHundreths);
	void setAngle(float angle);
	virtual fpDegrees getAngle();


	//
	//setPercent()
	//

	virtual void setPercent(fpPercent percentHundreths);
	void setPercent(float percent);
	virtual fpPercent getPercent();


	//
	//powerOff()
	//

	virtual void powerOff();


	//
	//powerOn()
	//

	virtual void powerOn();


	//
	//getFullRange()
	//

	virtual fpDegrees getFullRange();
};




#endif /* APPLICATION_SERVO_H_ */
