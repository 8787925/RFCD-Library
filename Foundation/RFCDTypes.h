/*
 * RFCDTypes.h
 *
 *  Created on: Mar 29, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_RFCDTYPES_H_
#define FOUNDATION_RFCDTYPES_H_

//#ifdef DEBUG
/* typedef unsigned int uint8_t;
 typedef int int8_t;
 typedef unsigned short uint16_t;
 typedef short int16_t;
 typedef unsigned long uint32_t;
 typedef long int32_t;
 typedef unsigned long long uint64_t;
//#endif
//
//TYPEDEFS
//*/
typedef unsigned long long uint64_t;
typedef uint64_t uSeconds;

#define uSECONDS_PER_SECOND 1000000ULL
#define uSECONDS_PER_MINUTE 60000000ULL
#define uSECONDS_PER_mSECOND 1000UL
#define mSECONDS_PER_SECOND 1000UL
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MINUTE 60

//typedef uint32_t mSeconds;
//typedef uint32_t Seconds; 
/*
struct Time{
	uSeconds Alarm;				//Timer threshhold for alarms
	uSeconds LongClockStamp;	//Current timer value in 1uS/bit
	uSeconds ElapsedTime;
	uSeconds T_One;				//Contains the ElapsedTime of the LAST acquired time; only refered to when calling 'Delta_T'
								//and only updated when 'Value' method is called.
	bool Running;				//Shows true if this timer is currently running or false if stopped/frozen
};*/


#endif /* FOUNDATION_RFCDTYPES_H_ */
