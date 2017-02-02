/*
 * TaskBlock.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\TaskBlock.h"

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\TaskManager.h"

//
//executeList()
//

void TaskBlock::executeList()
{
	uint8_t i =0;
	interrupted_=false;
	readyToRun_=false;

	if (isRunning_){PORTB^=(1<<6); }
	for (i=0; i<MAXTHREADS; i++)
	{
		if ((threadList_[i] != 0))//if it is not a null pointer
		{
			isRunning_=true;
			threadList_[i]->run();
		}
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

bool TaskBlock::decrementCountsBeforeNextRun()
{
	remainingCountBeforeRun_--; //decrement by a count

	if (!remainingCountBeforeRun_) //if it's time to run
	{	

		remainingCountBeforeRun_=countsBetweenRuns_;
		if (isRunning_)
		{
			PORTB ^= (1<<7);
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
}


//
//add(Thread&)
//

void TaskBlock::add(Thread* thread_)
{
	uint8_t i =0;
	for (i=0; i<MAXTHREADS; i++)
	{
		if (threadList_[i] == 0) //if it is not a null pointer
		{
			threadList_[i] = thread_;
			return;
		}
	}
}


//
//remove(Thread&)
//

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
}


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

TaskPriority TaskBlock::getPriority()
{
	return taskPriority_;
}


//
//getNumberOfThreads()
//

uint8_t TaskBlock::getNumberOfThreads()
{
	uint8_t threadCount = 0;
	uint8_t i =0;

	for (i=0; i<MAXTHREADS; i++)
	{
		if (threadList_[i] != 0 ) //if it is not a null pointer
		{
			threadCount++;
		}
	}

	return threadCount;
}


//
//constructor(uint16_t)
//

TaskBlock::TaskBlock(TaskPeriod_us countBetweenRuns,TaskPriority priority)
{
	taskPeriod_=countBetweenRuns;
	countsBetweenRuns_=((uint16_t)taskPeriod_)/RTC_PERIOD_USECONDS;

	if (!countsBetweenRuns_) //IF the count between runs is 0, then define it as 1 (meaning the between runs count rounds down to 0 at initialization)
	{
		countsBetweenRuns_=1;//task period cannot be zero through math errors
	}
	int i = 0;
	for (i=0; i<MAXTHREADS; i++)
	{
		threadList_[i] = 0;
	}
	taskPriority_ = priority;
	remainingCountBeforeRun_ = countsBetweenRuns_;
	holdTaskForInterruption_=false;
	readyToRun_=false;
	isRunning_=false;
	interrupted_=false;
	pausedThread_=0;
	//SystemTaskManager_->addPeriodic(this);
}
