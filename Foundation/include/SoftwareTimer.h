/*
 * SoftwareTimer.h
 *
 *  Created on: Mar 28, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SOFTWARETIMER_H_
#define FOUNDATION_SOFTWARETIMER_H_

//#include "RFCDTypes.h"
#include "Foundation\Listener.h"
#include "Foundation\Clock.h"
#include "Foundation\Counter.h"
#include "Foundation\PointerListKit.h"


class SoftwareTimer: public Counter, public Listener
{
public:
	//
	//constructor
	//

	SoftwareTimer(Clock* clock);
	SoftwareTimer(uSeconds uSecondsPerCall);


	//
	//listenerEvent()
	//
	//called on each tick of the clock

	void listenerEvent();


	//
	//hasElapsed(uSeconds)
	//

	bool hasElapsed(uSeconds timeCheck);


	//
	//getTime()
	//
	//returns the uSeconds on the clock

	uSeconds getTime();


	//
	//assignClock(Clock*)
	//

	void assignNewClock(Clock* clock);


	//
	//pause()
	//

	void pause();


	//
	//resume()
	//

	void resume();


	//
	//variables
	//

	uSeconds uSecondsPerCall_;
	Clock* clock_;
	bool paused_;
};


#endif /* FOUNDATION_SOFTWARETIMER_H_ */
