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

Fault::Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky, FaultAction* faultAction)
{
	faultID_ = faultID;
	faultTriggerLevel_ = faultTriggerCount;
	incrementBy_ = incrementBy;
	decrementBy_ = decrementBy;
	isSticky_ = isSticky;
	faultAction_ = faultAction;
	isEnabled_ = true;
}

Fault::Fault(uint16_t faultID, uint16_t faultTriggerCount, uint16_t incrementBy, uint16_t decrementBy, bool isSticky)
{
	faultID_ = faultID;
	faultTriggerLevel_ = faultTriggerCount;
	incrementBy_ = incrementBy;
	decrementBy_ = decrementBy;
	isSticky_ = isSticky;
	faultAction_ = 0;
	isEnabled_ = true;
}

