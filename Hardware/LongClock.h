/*
 * LongClock.h
 *
 *  Created on: Jun 14, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_LONGCLOCK_H_
#define HARDWARE_LONGCLOCK_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\MowerProject\config.h"
#include "LongClockConfig.h"

#define uSECONDS_PER_SECOND 1000000ULL
#define uSECONDS_PER_MINUTE 60000000ULL
#define uSECONDS_PER_mSECOND 1000UL
#define mSECONDS_PER_SECOND 1000UL
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MINUTE 60


class LongClock{
public:
	//
	//Instance
	//

	static LongClock * instance();


	//
	//uSeconds getTime()
	//
	//returns the Time in microseconds since the system powered on.

	uSeconds getTime();


	//
	//void setTime(uSeconds);
	//
	//Sets the current time to the received time.

	void setTime(uSeconds SetTime);


	//
	//void clockTop(uint32 uSeconds_Per_Top)
	//
	//called at each clock overrun

	void clockTop(uSeconds uSeconds_per_top);


	//
	//uint32_t getFrequency();
	//
	//returns the current system frequency in cycles per second - FCPU

	uint32_t getFrequency();

	Time SystemTime;
private:

	//
	//constructor()
	//
	
	LongClock();
};


#endif /* HARDWARE_LONGCLOCK_H_ */
