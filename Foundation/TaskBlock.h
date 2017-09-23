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

#include "config.h"
#include "Foundation\Thread.h"
#include "Foundation\RFCDTypes.h"

enum TaskPriority{
	INTERRUPT,
	HIGH,
	MEDIUM,
	REGULAR,
	LOW
};

enum TaskPeriod_us{
	ONEmsTASK=1000,
	TWOmsTASK=2000,
	FIVEmsTASK=5000,
	TENmsTASK=10000,
	TWENTYmsTASK=20000,
	FIFTYmsTASK = 50000,
	HUNDREDmsTASK=100000,
	ONEsTASK=1000000,
	BACKGROUND=1000001
};



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
