/*
 * Counter.h
 *
 *  Created on: Mar 28, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_COUNTER_H_
#define FOUNDATION_COUNTER_H_

#include "Foundation\RFCDTypes.h"
#include "Foundation\Listener.h"

enum CounterDirection
{
	COUNT_UP = 1,
	COUNT_DOWN = -1
};


enum CounterType
{
	WRAPPED,
	SINGLE,
	FREE,
	LIMITED
};


class Counter
{public:
	//
	//constructor
	//

	Counter(Listener* alarm, uint64_t CounterResetValue, CounterDirection Direction, CounterType Type);
	Counter(uint64_t CounterResetValue, CounterDirection Direction, CounterType Type);


	//
	//count()
	//
	//returns True when the counter reaches 0

	bool count();


	//
	//countBy(int16_t);
	//
	//returns the true or false nature of the counter, but increments or derements the count based on the value handed to the method
	//

	bool countBy(int16_t);


	//
	//getCount()
	//

	uint64_t getCount();
	void setCount(uint64_t newCount);


	//
	//reset()
	//
	//resets the current count to

	void reset();


	//
	//forceCompare()
	//
	//forces the timer to the TRUE state, and executes the alarm (if provided)


	void forceCompare();


	//
	//update(...)
	//
	//this method causes a reset of the counter

	void update(uint64_t CounterResetValue);
	void update(CounterDirection Direction);
	void update(CounterType Type);
	void update(Listener* listener);

private:
	//
	//variables
	//

	Listener* listener_;
	uint64_t currentCount_;
	uint64_t resetValue_;
	uint64_t trueOnThisValue_;
	bool enabled_;
	CounterDirection direction_;
	CounterType type_;
};


#endif /* FOUNDATION_COUNTER_H_ */
