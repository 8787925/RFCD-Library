/*
 * TaskManager.h
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_TASKMANAGER_H_
#define FOUNDATION_TASKMANAGER_H_

#include <avr/io.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\TaskBlock.h>

#define FOREGROUND_TASKS 3
#define BACKGROUND_TASK 1
#define MAXTASKS (FOREGROUND_TASKS + BACKGROUND_TASK)

//#define INCLUDE_BACKGROUND_TASK 1

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


class TaskBlock; //forward Declaration

class TaskManager {
public:
	//
	//instance()
	//

	static TaskManager* instance();


	//
	//addPeriodic(TaskBlock&)
	//

	void addPeriodic(TaskBlock* taskBlock);


	//
	//run()
	//

	void run(TaskPeriod_us period);

	void run();


	//
	//remove(TaskBlock&)
	//

	void remove(TaskBlock* taskblock);


	//
	//addSporatic(TaskBlock&, uint8_t);
	//

	void addSporatic(TaskBlock* taskBlock);


	//
	//callOnPrincipleinterval()
	//

	void callOnPrincipleInterval();

private:

	//
	//insertTaskToQue(TaskBlock&)
	//

	void insertTaskToQue(TaskBlock* task);


	//
	//removeTaskFromQue(TaskBlock*)
	//

	void removeTaskFromQue(TaskBlock* task);


	//
	//decrementAllCounts()
	//

	bool decrementAllCounts();


	//
	//determineInterrupt()
	//

	void determineInterrupt();


	//
	//constructor()
	//

	TaskManager();

	uint16_t callTicks_; //acting as the RTC, reveals the number of calls/principle ticks of the task manager
	TaskBlock* taskBlockList_[MAXTASKS];
	TaskBlock* taskBlockQue_[MAXTASKS];
	bool interruptArbitrationRequired_;
};



#endif /* FOUNDATION_TASKMANAGER_H_ */
