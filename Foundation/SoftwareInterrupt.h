/*
 * SoftwareInterrupt.h
 *
 *  Created on: Sep 16, 2016
 *      Author: Jimmy
 */

#ifndef SOFTWAREINTERRUPT_H_
#define SOFTWAREINTERRUPT_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\TaskManager.h"

class InterruptObject
{
public:
	//
	//activate()
	//

	void activate()
	{
		*Port_ |= (1<<Pin_);
		//presume the task is executed
		*Port_ &= ~(1<<Pin_);
	}


	//
	//mechanism(volatile Int)
	//

	InterruptObject(volatile uint8_t* Port, uint8_t Pin, TaskPeriod_us Period)
	{
		Period_=Period;
		Port_=Port;
		Pin_=Pin;
	}


	//
	//getPeriod()
	//

	TaskPeriod_us getPeriod()
	{
		return Period_;
	}

private:
	//
	//variables
	//

	volatile uint8_t* Port_;
	uint8_t Pin_;
	TaskPeriod_us Period_;
};



class SoftwareInterrupt
{
public:
	//
	//instance()
	//

	static SoftwareInterrupt* instance();


	//
	//determineInterrupt(TaskPeriod_us)
	//

	void determineInterrupt(TaskPeriod_us Period);


	//
	//add(InterruptObject*)
	//
	//LOOPS MUST BE ADDED IN ASCENDING ORDER

	void add(InterruptObject* Obj);

private:

	SoftwareInterrupt();

	//
	//variables
	//

	InterruptObject* taskLoops_[MAXTASKS-1];
};


#endif /* SOFTWAREINTERRUPT_H_ */
