/*
 * TaskBlock.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#include "Foundation\TaskBlock.h"

#include "Foundation\TaskManager.h"


//
//executeIfReady()
//

void TaskBlock::executeIfReady()
{
	if (readyToRun_)
	{
		this->executeList();
#if DEBUG
		cout << "exifready " << this->taskPeriod_ << endl;
#endif
	}
}


//
//executeList()
//

void TaskBlock::executeList()
{
	bool listExecution;
	interrupted_=false;
	readyToRun_=false;

	//if (isRunning_){PORTB^=(1<<6);} debug flagging

	isRunning_ = true;
	listExecution = true; //flag to begin at the top of the iteration list

	if (this->used() > 0) //guard against attempted execution of an empty list
	{
		do
		{
			this->iterate(&listExecution)->run();

		}while (!listExecution); //wait for 'true' to be returned, indicating a complete list execution
	}

	isRunning_=false;
}


//
//interruptTask()
//

void TaskBlock::interruptTask()
{
	if(isRunning_)
		{
			holdTaskForInterruption_=true;
		}
}


//
//resumeTask()
//

void TaskBlock::resumeTask()
{
	holdTaskForInterruption_=false;
	this->executeList();
}


//
//isReadyToRun();
//

bool TaskBlock::isReadyToRun()
{
	return readyToRun_;
}


//
//isRunning();
//

bool TaskBlock::isRunning()
{
	return isRunning_;
}


//
//getPeriod();
//

TaskPeriod_us TaskBlock::getPeriod()
{
	return taskPeriod_;
}


//
//isInterrupted();
//

bool TaskBlock::isInterrupted()
{
	return interrupted_;
}


//
//decrementCountsBeforeNextRun()
//
/*
bool TaskBlock::decrementCountsBeforeNextRun()
{
	remainingCountBeforeRun_--; //decrement by a count

	if (!remainingCountBeforeRun_) //if it's time to run
	{	

		remainingCountBeforeRun_=countsBetweenRuns_;
		if (isRunning_)
		{
			//PORTB ^= (1<<7); debug flagging
			////task has overrun #TODO add overrun flag registry
		}
		readyToRun_=true;
		return true;
	}
	else
	{
		//it is not time to run
		return false;
	}
}*/


//
//add(Thread&)
//
/*
void TaskBlock::add(Thread* thread_)
{
	uint8_t i =0;
	for (i=0; i<MAXTHREADS; i++)
	{
		if (threadList_[i] == 0) //if the list position has 'null' in it, it's good to have new data inserted
		{
			threadList_[i] = thread_;
			return;
		}
	}
}*/


//
//remove(Thread&)
//
/*
void TaskBlock::remove(Thread* thread_)
{
	uint8_t i =0;
	for (i=0; i<MAXTHREADS; i++)
	{
		if (thread_ != 0 && threadList_[i] == thread_ ) //if it is not a null pointer
		{
			threadList_[i] = 0;
		}
	}

	//this->reSortList();
}*/


//
//reSortList()
//

void TaskBlock::reSortList()
{
	//this isn't necessary for now
}


//
//getPriority();
//
/*
TaskPriority TaskBlock::getPriority()
{
	return taskPriority_;
}*/


//
//getNumberOfThreads()
//

uint8_t TaskBlock::getNumberOfThreads()
{

	return this->used();
}


//
//listenerEvent()
//

void TaskBlock::listenerEvent() //called at the expiration of the 'counter'
{
	readyToRun_ = true;
}

//
//constructor(uint16_t)
//

TaskBlock::TaskBlock(TaskPeriod_us countBetweenRuns,TaskPriority priority):Counter(this, 10000, COUNT_DOWN, WRAPPED) //counter is given artifical high value until guards are in place in constructor
{
	taskPeriod_=countBetweenRuns;
	ticksBetweenRuns_=((uint16_t)taskPeriod_)/RTC_PERIOD_USECONDS;

	if (!ticksBetweenRuns_) //IF the count between runs is 0, then define it as 1 (meaning the between runs count rounds down to 0 at initialization)
	{
		ticksBetweenRuns_=1;//task period cannot be zero through math errors
	}

	update(uint64_t (ticksBetweenRuns_)); //update the counter with the correct value once we've guarded against error values

	taskPriority_ = priority;
	holdTaskForInterruption_=false;
	readyToRun_=false;
	isRunning_=false;
	interrupted_=false;
	pausedThread_=0;
	//SystemTaskManager_->addPeriodic(this);
}
