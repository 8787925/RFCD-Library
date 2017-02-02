/*
 * Thread.h
 *
 *  Created on: Aug 9, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_THREAD_H_
#define FOUNDATION_THREAD_H_


class Thread
{
public: 
	
	virtual void run() = 0;

	~Thread(){}
};


#endif /* FOUNDATION_THREAD_H_ */
