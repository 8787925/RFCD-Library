/*
 * Fault.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: mattb
 */



#include "Fault.h"


//
//constructor
//

Fault::Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky, FaultAction* faultAction):
		Counter(faultTriggerCount, COUNT_UP, LIMITED)
{
	faultID_ = faultID;
	faultTriggerLevel_ = faultTriggerCount;
	incrementBy_ = incrementBy;
	decrementBy_ = decrementBy;
	isSticky_ = isSticky;
	faultAction_ = faultAction;
	isEnabled_ = true;
	faultIsSet_ = false;
}

Fault::Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky):
		Counter(faultTriggerCount, COUNT_UP, LIMITED)
{
	faultID_ = faultID;
	faultTriggerLevel_ = faultTriggerCount;
	incrementBy_ = incrementBy;
	decrementBy_ = decrementBy;
	isSticky_ = isSticky;
	faultAction_ = 0;
	isEnabled_ = true;
	faultIsSet_ = false;
}

//
//faultUpdate()
//
//increments a leak into the bucket if fault is true, decrements if fault is false
//returns true if the fault is set on that increment
//

bool Fault::faultUpdate()
{
	if (this->faultCondition())
	{
		faultIsSet_ |= this->countBy(incrementBy_);
	}
	else
	{
		faultIsSet_ |= this->countBy(decrementBy_);
	}

	return faultIsSet_;
}


//
//faultBucketStatus()
//
//calling this (presumably by a polling fault manager/agregator) returns the current status of the bucket
//it does not increment or decrement counts, nor is is able to clear or satisfy conditions of the fault
//

bool Fault::faultBucketStatus()
{
	return faultIsSet_;
}


//
//clearFault()
//
//resets the bucket to initial conditions and will clear a sticky fault
//

void Fault::clearFault()
{
	this->reset();
	faultIsSet_ = false;
}


//
//forceFault()
//
//sets the fault by incrementing the count to the threshhold value of the bucket
//implicitly this method sets a sticky fault
//

void Fault::forceFault()
{
	this->forceCompare();
	faultIsSet_ = true;
}

