/*
 * LongClock.h
 *
 *  Created on: Jun 14, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_LONGCLOCK_H_
#define HARDWARE_LONGCLOCK_H_

#include <C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\avr\include\stdint.h>

typedef uint64_t uSeconds;
typedef uint32_t mSeconds;
typedef uint32_t Seconds;

struct Time{
	uSeconds Alarm;				//Timer threshhold for alarms
	uSeconds LongClockStamp;	//Current timer value in 1uS/bit (1.19hr limit)
	uSeconds ElapsedTime;
	uSeconds T_One;				//Contains the ElapsedTime of the LAST acquired time; only refered to when calling 'Delta_T'
								//and only updated when 'Value' method is called.
	bool Running;				//Shows true if this timer is currently running or false if stopped/frozen
};

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

	void clockTop(uSeconds uSeconds_per_top);


	//
	//uint32_t getFrequency();
	//
	//returns the current system frequency - FCPU

	uint32_t getFrequency();

	Time SystemTime;
private:

	//
	//constructor()
	//
	
	LongClock();
};


#endif /* HARDWARE_LONGCLOCK_H_ */
