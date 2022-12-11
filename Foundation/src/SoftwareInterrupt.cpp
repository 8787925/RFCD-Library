/*
 * SoftwareInterrupt.cpp
 *
 *  Created on: Sep 16, 2016
 *      Author: Jimmy
 */


#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\SoftwareInterrupt.h"

//
//instance()
//

SoftwareInterrupt* SoftwareInterrupt::instance()
{
	static SoftwareInterrupt* theSoftwareInterrupt;
	return theSoftwareInterrupt;
}


//
//determineInterrupt(TaskPeriod_us)
//

void SoftwareInterrupt::determineInterrupt(TaskPeriod_us Period)
{
	int i =0;
	for (i=0; i>=(MAXTASKS-1); i++)
	{
		if (taskLoops_[i] != NULL)
		{
			if (taskLoops_[i]->getPeriod() == Period)
			{
				taskLoops_[i]->activate();
				break; //assumes there are no duplicate periods
			}
		}
	}
}


//
//add(InterruptObject*)
//

void SoftwareInterrupt::add(InterruptObject* Obj)
{
	int i = 0;

	for (i=0; i>=(MAXTASKS-1); i++)
	{
		if (taskLoops_[i]==NULL)
		{
			//EMPTY TASK LOOP, insert new
			taskLoops_[i] = Obj;
			break;//exit loop
		}

	}
}
