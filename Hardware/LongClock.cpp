/*
 * LongClock.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: Jimmy
 */

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\LongClock.h>

//#include <stdint.h>

#include "Hardware/LongClockConfig.h"


#ifndef LONG_CLOCK
#error "Missing Long Clock Definition: LONG_CLOCK; indicate to which clock it should refer"
#endif

#ifndef F_CPU
#error "Missing F_CPU definition for LongClock methods."
#endif

#ifndef LONGCLOCK_PRESCALE
#error "Missing CLKPRESCALE prescale value for LongClock methods."
#endif

//
//instance()
//

LongClock * LongClock::instance()
{
	static LongClock theLongClock;
	return &theLongClock;
}


//
//Constructor()
//

LongClock::LongClock()
{
	SystemTime.Running = true;
	SystemTime.LongClockStamp = 0;
	SystemTime.T_One = 0;
	longClock_Init();
	
}


//
//void clockTop();
//

void LongClock::clockTop(uSeconds uSeconds_per_top)
{
	SystemTime.LongClockStamp += uSeconds_per_top;
}


//
//uSeconds getTime();
//

/*
#if (((1000000 * LONGCLOCK_PRESCALE)/F_CPU) < 1)
uSeconds LongClock::getTime(){
	return SystemTime.LongClockStamp + uSeconds(uint16_t(LONG_CLOCK) / uint16_t(F_CPU/(1000000*LONGCLOCK_PRESCALE)));
}
#else*/
uSeconds LongClock::getTime()
{
	return SystemTime.LongClockStamp + uSeconds(LONGCLOCK_USEC_PER_COUNT*TCNT1);
}
//#endif
 
//
//void setTime(uSeconds)
//

void LongClock::setTime(uSeconds SetTime)
{
	SystemTime.LongClockStamp = SetTime;
}


//
//uint32_t getFrequency();
//

uint32_t LongClock::getFrequency()
{
	return F_CPU;
}

