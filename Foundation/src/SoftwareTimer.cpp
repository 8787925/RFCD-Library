/*
 * SoftwareTimer.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: mattb
 */

#include "Foundation\SoftwareTimer.h"

//
//constructor(s)
//

SoftwareTimer::SoftwareTimer(Clock* clock): Counter(0, COUNT_UP, CounterType::FREE)
{
	clock_ = clock;
	uSecondsPerCall_ = clock->getuSecondsPerTick();
	clock->add(this);
	paused_ = false;
};


SoftwareTimer::SoftwareTimer(uSeconds uSecondsPerCall): Counter(0, COUNT_UP, CounterType::FREE)
{
	clock_ = 0;
	uSecondsPerCall_ = uSecondsPerCall;
	paused_ = false;
};


//
//hasElapsed(uSeconds)
//

bool SoftwareTimer::hasElapsed(uSeconds timeCheck)
{
	return (this->getTime() > timeCheck);
}


//
//listenerEvent()
//

void SoftwareTimer::listenerEvent()
{
	if (!paused_)
	{
		this->count();
	}
}


//
//pause()
//

void SoftwareTimer::pause()
{
	paused_ = true;
}


//
//resume()
//

void SoftwareTimer::resume()
{
	paused_ = false;
}


//
//assignNewClock(Clock*)
//

void SoftwareTimer::assignNewClock(Clock* clock)
{
	clock_ = clock;
	uSecondsPerCall_ = clock->getuSecondsPerTick();
	this->reset();
}


//
//getTime()
//


uSeconds SoftwareTimer::getTime()
{
	return (uSecondsPerCall_ * this->getCount());
}


