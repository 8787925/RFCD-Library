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
	uint8_t i_=0;

  	for (i_=0; i_<MAXTASKS; i_++)
 	{  
	
		if (taskBlockList_[i_]!=NULL)
		{
			if ( (period == taskBlockList_[i_]->getPeriod()) && (!taskBlockList_[i_]->isRunning()) )
			{
				taskBlockList_[i_]->executeList();
			}
		}
	}
	
}


//
//run()
//

void TaskManager::run()
{
	if (taskBlockQue_[0]!=NULL)
	{
		//if the 0th task is already being run, it means the inserted/arbitrated task
		//was not of a high enough priority
		if (!taskBlockQue_[0]->isRunning() && taskBlockQue_[0]->isReadyToRun())
		{
			taskBlockQue_[0]->executeList();
			//assume that arrival here means the task is finished and can be removed from Que
			this->removeTaskFromQue(taskBlockQue_[0]);
		}
		interruptArbitrationRequired_ = false;
	}
}


//
//addPeriodic(TaskBlock&)
//

void TaskManager::addPeriodic(TaskBlock* taskBlock)
{	uint8_t i = 0; 
	
	for (i=0; i<MAXTASKS; i++)
	{
		if (taskBlockList_[i] == 0)
		{
			taskBlockList_[i] = taskBlock;
			return;
		}
	}
}


//
//decrementAllCounts()
//

bool TaskManager::decrementAllCounts()
{
	uint8_t i=0;
	bool taskNeedsToBeStarted;
	taskNeedsToBeStarted=false;
	for (i=0; i<MAXTASKS; i++)
	{
		if (taskBlockList_[i]!=0)
		{
			taskNeedsToBeStarted|=taskBlockList_[i]->decrementCountsBeforeNextRun();
		}
	}

	return taskNeedsToBeStarted;
}


//
//determineInterrupt()
//

void TaskManager::determineInterrupt()
{
	uint8_t i=0;

	for (i=0; i<MAXTHREADS; i++)
	{
		if ((taskBlockList_[i]!=0) && (taskBlockList_[i]->isReadyToRun()))// && !(taskBlockList_[i]->isRunning())) //indicates the task is responsible for an interrupt request
		{
			//principle and background tasks are excluded from the cue because they run on a hardware interrupt
			if ((taskBlockList_[i]->getPeriod() != BACKGROUND) && (taskBlockList_[i]->getPeriod() != TaskPeriod_us(PRINCIPLE_TASK_PERIOD)))
			{
				this->insertTaskToQue(taskBlockList_[i]);
			}
		}
	}
}


//
//insertTaskToQue(TaskBlock&)
//

void TaskManager::insertTaskToQue(TaskBlock* task)
{
	uint8_t i=0;
	TaskBlock* temporaryStorage;

	if (taskBlockQue_[MAXTASKS-1]==NULL)//there's space for inserting a new item
	{
		if (taskBlockQue_[0]==NULL) //nothing's actually in the cue, add the new one to position 0
		{
			taskBlockQue_[0] = task;
			return;
		}

		//
		//insert the new task into the first available empty space in cue, when starting from the bottom
		//

		for (i=MAXTASKS-1; i>=0; i--) //increment through the list bottom to top, from the second to last spot to the top
		{
			if (taskBlockQue_[i] != NULL) //if the list entry is empty
			{
				//insert into that empty place
				taskBlockQue_[i] = task;
				break;
			}
		}

		//
		//organize the cue's new entry, by walking from bottom of the list to the top
		//

		for (i=MAXTASKS-1; i>=1; i--)
		{
			if (taskBlockQue_[i] != NULL) //if the position in the que isn't empty
			{//check to see if the position above it is of a higher rate
				if (taskBlockQue_[i-1]->getPeriod() > taskBlockQue_[i]->getPeriod()) //if the task one above the I entry is running slower, move the I entry up
				{
					temporaryStorage = taskBlockQue_[i];
					taskBlockQue_[i] = taskBlockQue_[i-1];
					taskBlockQue_[i-1] = temporaryStorage;
				}

			}
		}
	}

}


//
//removeTaskFromQue(TaskBlock*)
//

void TaskManager::removeTaskFromQue(TaskBlock* task)
{
	int i = 0;
	int shift = 0;

	//
	//delete the offered task
	//
	for (i=0; i<MAXTASKS; i++)
	{
		if (taskBlockQue_[i] != 0)
		{
			if (taskBlockQue_[i] == task)
			{
				taskBlockQue_[i] = 0;
			}
		}
	}

	//
	//shift the remainder of the list upward
	//
	for (i=0; i<MAXTASKS-1; i++)
	{
		if (taskBlockQue_[i] == 0) //if the current entry is 0, then promote the entry just below it in list
		{
			taskBlockQue_[i] = taskBlockQue_[i+1];
			taskBlockQue_[i+1] = 0;
		}
	}

}


//
//callOnPrincipleinterval()
//

void TaskManager::callOnPrincipleInterval()
{
	interruptArbitrationRequired_=this->decrementAllCounts();
	if (interruptArbitrationRequired_)
	{
		this->determineInterrupt();
	}
	if (taskBlockQue_[0] != NULL)
	{
		if (!taskBlockQue_[0]->isRunning())
		{
			this->run();
		}
	}
}


//
//constructor()
//

TaskManager::TaskManager()
{
	callTicks_=0;
	interruptArbitrationRequired_=false;
}
