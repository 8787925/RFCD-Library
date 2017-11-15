/*
 * SoftwareAlarm.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: mattb
 */

#include "Foundation\SoftwareAlarm.h"
#include "Foundation\SoftwareTimer.h"


//
//constructor
//

SoftwareAlarm::SoftwareAlarm(uSeconds uSecondsPerCall, uSeconds alarmTime,
		Listener* alarm, AlarmType type): SoftwareTimer (uSecondsPerCall)
{
	alarmFunction_ = alarm;
	type_ = type;
	alarmTime_ = alarmTime;
	this->update(alarm);
	this->update(uint64_t(alarmTime / uSecondsPerCall_));
}

SoftwareAlarm::SoftwareAlarm(uSeconds alarmTime,
		Listener* alarm, Clock* clock, AlarmType type): SoftwareTimer (clock)
{
	alarmFunction_ = alarm;
	type_ = type;
	this->update(alarm);
	this->update(uint64_t(alarmTime / uSecondsPerCall_));
	if (type_ == REPEAT_LOOP)
	{
		this->update(CounterType::WRAPPED);
	}
	else if (type_ == SINGLE_USE)
	{
		this->update(CounterType::SINGLE);
	}
	alarmTime_ = alarmTime;
}

//
//getAlarmTime()
//

uSeconds SoftwareAlarm::getAlarmTime()
{
	return alarmTime_;
}


//
//setAlarmTime()
//

void SoftwareAlarm::setAlarmTime(uSeconds alarmTime)
{
	alarmTime_ = alarmTime;
	this->update(uint64_t (alarmTime / uSecondsPerCall_));
}


//
//setAlarmFunction(Listener*)
//

void SoftwareAlarm::setAlarmFunction(Listener* listenerFunction)
{
}


//
//hasExpired()
//

bool SoftwareAlarm::hasExpired()
{
	return false;
}
