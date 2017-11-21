/*
 * TaskManager.h
 *
 *  Created on: Aug 10, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_TASKMANAGER_H_
#define FOUNDATION_TASKMANAGER_H_

#ifndef UNIT_TESTING
	#include <avr/io.h>
#endif

#include <Foundation\TaskBlock.h>
#include <Foundation\SortedPointerListKit.h>

#ifndef FOREGROUND_TASKS
	#define FOREGROUND_TASKS 3
#endif

#ifndef BACKGROUND_TASK
	#define BACKGROUND_TASK 1
#endif

#define MAXTASKS (FOREGROUND_TASKS + BACKGROUND_TASK)

//#define INCLUDE_BACKGROUND_TASK 1


class TaskManager: public SortedList <MAXTASKS, TaskBlock, TaskPeriod_us>
{
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
	//addSporatic(TaskBlock&, uint8_t);
	//

	void addSporatic(TaskBlock* taskBlock);


	//
	//callOnPrincipleinterval()
	//

	void callOnPrincipleInterval();

private:
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

	bool interruptArbitrationRequired_;
};



#endif /* FOUNDATION_TASKMANAGER_H_ */
