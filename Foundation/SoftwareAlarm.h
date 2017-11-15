/*
 * SoftwareAlarm.h
 *
 *  Created on: Mar 29, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SOFTWAREALARM_H_
#define FOUNDATION_SOFTWAREALARM_H_

#include "Foundation\SoftwareTimer.h"
#include "Foundation\Listener.h"

enum AlarmType{
	REPEAT_LOOP,
	SINGLE_USE
};

class SoftwareAlarm: public SoftwareTimer
{
public:
	//
	//constructor
	//

	SoftwareAlarm (uSeconds uSecondsPerCall, uSeconds alarmTime, Listener* alarm, AlarmType type);
	SoftwareAlarm (uSeconds alarmTime, Listener* alarm, Clock* clock, AlarmType type);

	//
	//getAlarmTime()
	//

	uSeconds getAlarmTime();

	void setAlarmTime(uSeconds alarmTime);


	//
	//setAlarmFunction(Listener* )
	//

	void setAlarmFunction(Listener* listenerFunction);


	//
	//hasExpired()
	//

	bool hasExpired();

private:
	//
	//variables
	//

	Listener* alarmFunction_;
	uSeconds alarmTime_;
	AlarmType type_;
};



#endif /* FOUNDATION_SOFTWAREALARM_H_ */
