/*
 * ListKit.h
 *
 *  Created on: Jan 22, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_POINTERLISTKIT_H_
#define FOUNDATION_POINTERLISTKIT_H_

#ifndef __STDINT_H_
#include "Application\TestAdapter.h"
#endif

#define POINTER_flag_EMPTY_position 3
#define POINTER_flag_ROLLING_position 2
#define POINTER_flag_EOL_position 1
#define POINTER_flag_SOL_position 0

#define POINTER_flagACT_SOL_position 4
#define POINTER_flagACT_ROLL_position 5

#define POINTER_stat_ROLLING (1<< POINTER_flag_ROLLING_position)
#define POINTER_stat_EOL (1<< POINTER_flag_EOL_position)
#define POINTER_stat_SOL (1<< POINTER_flag_SOL_position)
#define POINTER_stat_LISTEMPTY (1<< POINTER_flag_EMPTY_position)

#define POINTER_act_SOL (1<<POINTER_flagACT_SOL_position)
#define POINTER_act_ROLL (1<< POINTER_flagACT_ROLL_position)


template <class T, const uint8_t LENGTH>

class PointerList
{
public:
	//
	//constructor
	//

	PointerList()
	{
		listFree_ = LENGTH;
		iterator_ = 0;
		listSize_ = listFree_;

		for (int i = 0; i<LENGTH; i++)
		{
			list_[i] = 0;
		}
	}


	//
	//length()
	//

	uint8_t length()
	{
		return LENGTH;
	}


	//
	//used()
	//

	uint8_t used()
	{
		return LENGTH - listFree_;
	}


	//
	//add(T*)
	//

	bool add(T* value)
	{
		bool success = false;

		for (int i = 0; i<LENGTH; i++)
		{
			if ((list_[i] == 0) || (list_[i] == value))
			{
				list_[i] = value;
				success = true;
				listFree_--;
				break;
			}
		}

		return success;
	}


	//
	//addToTop(T*)
	//

	bool addToTop(T* value)
	{
		bool success = false;

		if (list_[LENGTH-1] == 0)
		{
			this->deleteShiftDown(LENGTH-1);
			success = this->add(value);
			listFree_--;
		}

		return success;
	}


	//
	//remove(T*)
	//

	bool remove(T* value)
	{
		bool success = false;

		for (int i = 0; i<LENGTH; i++)
		{
			if (list_[i] == value)
			{
				list_[i] = 0;
				this->deleteShiftUp(i);
				success = true;
				listFree_++;
				break;
			}
		}

		return success;
	}


	//
	//deleteFirst()
	//

	void deleteFirst()
	{
		this->deleteShiftUp(0);
	}


	//
	//iterate()
	//

	T* iterate(uint8_t* listStatus)
	{
		if (*listStatus & POINTER_act_SOL) //if client requests to start from list beginning
		{
			iterator_ = 1;
		}
		else
		{
			iterator_ ++;
		}


		if (iterator_ == LENGTH) //wrap to the beginning of the list if the end
		{
			iterator_ = 1;
		}

		switch (iterator_)
		{
			case (LENGTH): //end of the list has been hit
					*listStatus |= POINTER_stat_EOL;
					break;

			case (1): //start of the list is hit
					*listStatus |= POINTER_stat_SOL;
					break;
		}

		*listStatus &= 0x0F; //clear the action flags

		return list_[iterator_-1];
	}

	T* iterate(bool* newLoop)
	{
		if ( *newLoop)
		{
			iterator_ = 0;
			*newLoop = false;
		}

		if (iterator_ < LENGTH)
		{
			iterator_++;
			if ((iterator_) >= this->used()) //if this is the last entry
			{
				*newLoop = true;
			}

			if (list_[iterator_-1] == 0) //if the entry is empty
			{
				*newLoop = true;
			}

			return list_[iterator_-1];
		}

		*newLoop = true;
		return 0;
	}


	//
	//get(uint8)
	//

	T* get(uint8_t position)
	{
		if (position < LENGTH)
		{
			return list_[position];
		}
		else
		{
			return 0;
		}
	}


private:
	//
	//deleteShiftUp(uint8_t)
	//

	void deleteShiftUp(uint8_t position)
	{
		if (position < LENGTH)
		{
			for (int i = position; i<LENGTH; i++)
			{
				if (i != LENGTH-1)
				{
					list_[i] = list_[i+1];
				}
				else //last entry is written as zero in the list
				{
					list_[i] = 0;
				}
			}
		}
	}


	//
	//deleteShiftDown(uint8_t)
	//

	void deleteShiftDown(uint8_t position)
	{
		if (position < LENGTH)
		{
			for (int i = position; i>=0; i--)
			{
				if (i != 0)
				{
					list_[i] = list_[i-1];
				}
				else //first entry is written as zero in the list
				{
					list_[i] = 0;
				}
			}
		}
	}


	//
	//variables
	//

	uint8_t listSize_, iterator_, listFree_;
	T* list_[LENGTH];
};



#endif /* FOUNDATION_POINTERLISTKIT_H_ */
