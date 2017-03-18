/*
 * PointerBuffer.h
 *
 *  Created on: Jan 31, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_POINTERBUFFER_H_
#define FOUNDATION_POINTERBUFFER_H_

#include "PointerListKit.h"

template <class T, const uint8_t BUFFERLENGTH>

class FifoPointerBuffer: public PointerList <T, BUFFERLENGTH>
{public:
	//
	//constructor
	//

	FifoPointerBuffer()
	{

	}


	//
	//dismiss()
	//

	void dismiss()
	{
		this->deleteFirst();
	}


	//
	//hasContent()
	//

	bool hasContent()
	{
		if (this->list_[0] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	//
	//isFull()
	//

	bool isFull()
	{
		if (this->list_[BUFFERLENGTH-1] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};



template <class T, const uint8_t BUFFERLENGTH>

class PriorityPointerBuffer: public PointerList <T, BUFFERLENGTH>
{

};



#endif /* FOUNDATION_POINTERBUFFER_H_ */
