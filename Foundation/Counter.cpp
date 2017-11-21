/*
 * Counter.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: mattb
 */

#include "RFCDTypes.h"
#include "Counter.h"

//
//constructor
//

Counter::Counter(Listener* alarm, uint64_t CounterResetValue,
		CounterDirection Direction, CounterType Type)
{
	listener_ = alarm;
	resetValue_ = CounterResetValue;
	direction_ = Direction;
	type_ = Type;
	enabled_ = true;

	if (direction_ == COUNT_UP)
	{
		trueOnThisValue_ = resetValue_;
		currentCount_ = 0;
	}
	else
	{
		trueOnThisValue_ = 0;
		currentCount_ = resetValue_;
	}
};


Counter::Counter(uint64_t CounterResetValue, CounterDirection Direction,
		CounterType Type)
{
	listener_ = 0;
	resetValue_ = CounterResetValue;
	direction_ = Direction;
	type_ = Type;
	enabled_ = true;

	if (direction_ == COUNT_UP)
	{//is count up timer
		trueOnThisValue_ = resetValue_;
		currentCount_ = 0;
	}
	else
	{//is count down timer
		trueOnThisValue_ = 0;
		currentCount_ = resetValue_;
	}

};


//
//count()
//


bool Counter::count()
{
	currentCount_ += (direction_ * (1 & enabled_));

	if (currentCount_ == trueOnThisValue_)
	{
		if (type_ == WRAPPED)
		{
			if (listener_ != 0)
			{
				listener_->listenerEvent();
			}

			this->reset();
		}
		else if (type_ == SINGLE)
		{
			if (enabled_ && (listener_ != 0))
			{
				listener_->listenerEvent();
			}

			enabled_ = false;
		}
		else if (type_ == FREE)
		{
			if (listener_ != 0)
			{
				listener_->listenerEvent();
			}
		}

		return true;
	}

	return false;
}


//
//forceCompare()
//

void Counter::forceCompare()
{
	if (direction_ == COUNT_UP)
	{
		currentCount_ = (trueOnThisValue_ -1);
	}
	else
	{
		currentCount_ = (trueOnThisValue_ +1);
	}

	this->count();
}


//
//reset()
//


void Counter::reset()
{
	enabled_ = true;

	if (direction_ == COUNT_UP)
	{
		currentCount_ = 0;
	}
	else
	{
		currentCount_ = resetValue_;
	}
}


//
//getCount()
//

uint64_t Counter::getCount()
{
	return currentCount_;
}


//
//update(...)
//


void Counter::update(uint64_t CounterResetValue)
{
	resetValue_ = CounterResetValue;

	if (direction_ == COUNT_UP)
	{
		trueOnThisValue_ = resetValue_;
		if (currentCount_ > trueOnThisValue_)
		{
			this->forceCompare();
		}
	}
	else
	{//is count down
		trueOnThisValue_ = 0;
		//currentCount_ = resetValue_;
		if (currentCount_ > resetValue_) //maintains the current count's scheduled arrival if possible
		{//the current count is bigger than our new counter size
			currentCount_ = resetValue_;
			//this->forceCompare();
		}
	}

	//this->reset();
}


void Counter::update(CounterDirection Direction)
{
	direction_ = Direction;

	if (direction_ == COUNT_UP)
	{
		trueOnThisValue_ = resetValue_;
		currentCount_ = 0;
	}
	else
	{
		trueOnThisValue_ = 0;
		currentCount_ = resetValue_;
	}

	this->reset();
}


void Counter::update(CounterType Type)
{
	type_ = Type;
	this->reset();
}


void Counter::update(Listener* listener)
{
	listener_ = listener;
	this->reset();
}



