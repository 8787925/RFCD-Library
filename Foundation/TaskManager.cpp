/*
 * TaskManager.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */


#include "Foundation\TaskManager.h"

//
//instance()
//

TaskManager* TaskManager::instance()
{
	static TaskManager theTaskManager;
	return &theTaskManager;
}


//
//run(TaskPeriod_us)
//

void TaskManager::run(TaskPeriod_us period)
{

  	for (int i=0; i<MAXTASKS; i++) //for all items in the list
 	{  
		if (this->get(i) != NULL) //guard against null pointer
		{//the pointer wasn't null, valid task found
			if ( (period == this->get(i)->getPeriod()) && (!this->get(i)->isRunning())) //if the task is both not running and the one we'd like to run
			{
				this->get(i)->executeList(); //run the task
				break;
			}
		}
		else
		{//the task is a null task, and since we're searching from the list top down, we can assume the remainder of this list will be empty
			break;
		}
	}
  	return;
}


//
//run()
//

void TaskManager::run()
{

}


//
//addPeriodic(TaskBlock&)
//

void TaskManager::addPeriodic(TaskBlock* taskBlock)
{

	this->add(taskBlock, &taskBlock->taskPeriod_);

}


//
//decrementAllCounts()
//

bool TaskManager::decrementAllCounts()
{
	bool taskNeedsToBeStarted;
	taskNeedsToBeStarted=false;
	bool listStatus = true;

	if (this->used() > 0) //guard against empty list/null pointer return
	{
		do
		{
			taskNeedsToBeStarted |= this->iterate(&listStatus)->count();
		}while (!listStatus);
	}

	return taskNeedsToBeStarted;
}


//
//determineInterrupt()
//

void TaskManager::determineInterrupt()
{
	//this section needs to stay away from the iterator, because it's not thread safe to access that variable for any
	//reason other than the 'decrement all counters' methods
	for (int i = 0; i < MAXTASKS; i++)//for all list positions
	{
		if (this->get(i) != 0) //if there's a valid pointer
		{
			this->get(i)->executeIfReady();
		}
	}
}


//
//callOnPrincipleinterval()
//

void TaskManager::callOnPrincipleInterval()
{
	interruptArbitrationRequired_=this->decrementAllCounts(); //find all ready to run flags

	if (interruptArbitrationRequired_)
	{
		this->determineInterrupt(); //executes all ready to run tasks
	}
}


//
//constructor()
//

TaskManager::TaskManager(): SortedList<MAXTASKS, TaskBlock, TaskPeriod_us> (bool(true))
{
	interruptArbitrationRequired_=false;
}
