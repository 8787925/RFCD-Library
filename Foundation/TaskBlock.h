/*
 * TaskBlock.h
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_TASKBLOCK_H_
#define FOUNDATION_TASKBLOCK_H_
#include <avr/io.h>
#define MAXTHREADS 5
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Thread.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\TaskManager.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\LongClock.h"



class TaskBlock
{
public:
	//
	//executeList();
	//

	void executeList();


	//
	//isReadyToRun();
	//

	bool isReadyToRun();


	//
	//getPeriod();
	//

	TaskPeriod_us getPeriod();


	//
	//getPriority();
	//

	TaskPriority getPriority();


	//
	//isInterrupted();
	//

	bool isInterrupted();


	//
	//isRunning();
	//

	bool isRunning();


	//
	//getNumberOfThreads();
	//

	uint8_t getNumberOfThreads();


	//
	//decrementCountsBeforeNextRun()
	//

	bool decrementCountsBeforeNextRun();


	//
	//add(&Thread)
	//

	void add(Thread* thread_);


	//
	//remove(&thread)
	//

	void remove(Thread* thread_);


	//
	//interruptTask()
	//

	void interruptTask();


	//
	//resumeTask()
	//

	void resumeTask();


	//
	//constructor()
	//

	TaskBlock(TaskPeriod_us countBetweenRuns, TaskPriority priority);


		
private:

	//
	//reSortList()
	//

	void reSortList();

	Thread *threadList_[MAXTHREADS];
	TaskPeriod_us taskPeriod_;
	TaskPriority taskPriority_;
	bool readyToRun_;
	bool isRunning_;
	bool interrupted_;
	uint8_t pausedThread_;
	uint16_t countsBetweenRuns_;
	uint16_t remainingCountBeforeRun_;
	bool holdTaskForInterruption_;
	//TaskManager* SystemTaskManager_ = TaskManager::instance();


};

#endif /* FOUNDATION_TASKBLOCK_H_ */
