/*
 * TaskBlock.h
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_TASKBLOCK_H_
#define FOUNDATION_TASKBLOCK_H_

#ifndef UNIT_TESTING
	#include <avr/io.h>
#endif

#define MAXTHREADS 5

#include "config.h"
#include "Foundation\Thread.h"
#include "Foundation\RFCDTypes.h"
#include "Foundation\PointerListKit.h"
#include "Foundation\Counter.h"

enum TaskPriority{
	INTERRUPT,
	HIGH,
	MEDIUM,
	REGULAR,
	LOW
};

typedef uint64_t TaskPeriod_us;

enum TaskPeriod{
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



class TaskBlock: public PointerList<Thread, MAXTHREADS>, private Listener, public Counter
{
public:
	//
	//executeIfReady()
	//

	void executeIfReady();


	//
	//executeList();
	//

	void executeList();


	//
	//listenerEvent()
	//
	//used to trigger the isReady_ boolean, once the timer has elapsed for the task
	//

	void listenerEvent();


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

	//TaskPriority getPriority();  eliminated by addition of PointerList class


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

	//bool decrementCountsBeforeNextRun(); no longer needed by adding Count class


	//
	//add(&Thread)
	//

	//void add(Thread* thread_); eliminated by addition of PointerList


	//
	//remove(&thread)
	//

	//void remove(Thread* thread_); eliminated by addition of PointerList


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


	TaskPeriod_us taskPeriod_; //access is necessary for the task manager

private:

	//
	//reSortList()
	//

	void reSortList();


	TaskPriority taskPriority_;
	bool readyToRun_;
	bool isRunning_;
	bool interrupted_;
	uint8_t pausedThread_;
	uint16_t ticksBetweenRuns_;
	bool holdTaskForInterruption_;
	//TaskManager* SystemTaskManager_ = TaskManager::instance();


};

#endif /* FOUNDATION_TASKBLOCK_H_ */
