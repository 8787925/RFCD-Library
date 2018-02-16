/*
 * Faut.h
 *
 *  Created on: Feb 13, 2018
 *      Author: mattb
 */

#ifndef FOUNDATION_FAULT_H_
#define FOUNDATION_FAULT_H_

#include "Counter.h"

class FaultAction //someone else outside our class (maybe inside) should have an e-stop button at fault.
{
	virtual runFaultAction(uint16_t faultID)=0;
};

class Fault: public Counter
{
public:
	//
	//constructor
	//

	Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky, FaultAction* faultAction);
	Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky);


	//
	//faultUpdate()
	//
	//increments a leak into the bucket if fault is true, decrements if fault is false
	//returns true if the fault is set on that increment
	//

	bool faultUpdate();


	//
	//faultBucketStatus()
	//
	//calling this (presumably by a polling fault manager/agregator) returns the current status of the bucket
	//it does not increment or decrement counts, nor is is able to clear or satisfy conditions of the fault
	//

	bool faultBucketStatus();


	//
	//faultBucketCount()
	//
	//returns the current count within the bucket
	//

	uint16_t faultBucketCount()
	{
		return this->getCount();
	}


	//
	//faultCondition()
	//
	//should be housed in higher classes, is called by faultUpdate in poll of whether the fault condition is currently true or false
	//

	virtual bool faultCondition() //always returns false unless overriden
	{
		return false;
	}


	//
	//clearFault()
	//
	//resets the bucket to initial conditions and will clear a sticky fault
	//

	void clearFault();


	//
	//forceFault()
	//
	//sets the fault by incrementing the count to the threshhold value of the bucket
	//implicitly this method sets a sticky fault
	//

	void forceFault();


	//
	//setFaultID(uint6_t)
	//
	//sets the faultID of the class
	//

	void setFaultID(uint16_t faultID)
	{
		faultID_ = faultID;
	}

	uint16_t getFaultID()
	{
		return faultID_;
	}


	//
	//enable(bool)
	//
	//enables or disables the bucket from both being filled and emptied
	//

	void enable(bool isEnabled)
	{
		isEnabled_ = isEnabled;
	}


	//
	//isEnabled();
	//
	//returns the enable/disable status of the class
	//

	bool isEnabled()
	{
		return isEnabled_;
	}

private:
	//
	//variables
	//

	bool isEnabled_;
	bool faultIsSet_;
	uint16_t incrementBy_, decrementBy_;
	uint16_t faultTriggerLevel_;
	uint16_t faultID_;
	bool isSticky_;
	FaultAction* faultAction_;

};


#endif /* FOUNDATION_FAULT_H_ */
