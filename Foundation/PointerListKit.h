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

#define POINTER_flag_SUCCESS_position 5
#define POINTER_flag_FULL_position 4
#define POINTER_flag_EMPTY_position 3
#define POINTER_flag_ROLLING_position 2
#define POINTER_flag_EOL_position 1
#define POINTER_flag_SOL_position 0

//todo add a macro to clear flags and to clear statuses, you already fucked this up once

#define POINTER_flagACT_SOL_position 6
#define POINTER_flagACT_ROLL_position 7

#define POINTER_stat_ROLLING (1<< POINTER_flag_ROLLING_position)
#define POINTER_stat_EOL (1<< POINTER_flag_EOL_position)
#define POINTER_stat_SOL (1<< POINTER_flag_SOL_position)
#define POINTER_stat_LISTEMPTY (1<< POINTER_flag_EMPTY_position)
#define POINTER_stat_LISTFULL (1 << POINTER_flag_FULL_position)
#define POINTER_stat_SUCCESS (1<< POINTER_flag_SUCCESS_position)
#define POINTER_stat_FAILURE 0

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
		return LENGTH - this->listFree_;
	}


	//
	//free()
	//

	uint8_t free()
	{
		return this->listFree_;
	}


	//
	//add(T*)
	//

	uint8_t add(T* value)
	{
		uint8_t success = false;

		for (int i = 0; i<LENGTH; i++)
		{
			if ((list_[i] == 0) || (list_[i] == value))
			{
				list_[i] = value;
				success = POINTER_stat_SUCCESS;
				this->claimFromFree();
				break;
			}
		}

		if (this->free() == 0)
		{
			success |= POINTER_stat_LISTFULL;
		}
		return success;
	}


	//
	//addToTop(T*)
	//

	uint8_t addToTop(T* value)
	{
		uint8_t success = false;

		if (list_[LENGTH-1] == 0)
		{
			this->deleteShiftDown(LENGTH-1);
			success = this->add(value);
		}

		return success;
	}


	//
	//remove(T*)
	//

	uint8_t remove(T* value)
	{
		uint8_t success = false;

		for (int i = 0; i<LENGTH; i++)
		{
			if (list_[i] == value)
			{
				list_[i] = 0;
				this->deleteShiftUp(i);
				success = POINTER_stat_SUCCESS;
				break;
			}
		}

		if (this->used() == 0) //flag if the list is empty
		{
			success |= POINTER_stat_LISTEMPTY;
		}

		return success;
	}


	//
	//deleteFirst()
	//

	uint8_t deleteFirst()
	{
		this->deleteShiftUp(0);

		if (this->used() == 0 ) // flag if the list is empty
		{
			return POINTER_stat_LISTEMPTY;
		}
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


		if (iterator_ == (LENGTH+1)) //wrap to the beginning of the list if the end
		{
			iterator_ = 1;
		}

		switch (iterator_)
		{
			case (LENGTH): //end of the list has been hit
					*listStatus &= 0xF0;
					*listStatus |= POINTER_stat_EOL;
					break;

			case (1): //start of the list is hit
					*listStatus &= 0xF0;
					*listStatus |= POINTER_stat_SOL;
					break;

			default: //neither the beginning nor the end of the list
					*listStatus &= 0xF0;
					*listStatus |= POINTER_stat_ROLLING;
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


	//
	//insert(T*, uint8_t)
	//
	//inserts at the position handed in the integer, shifting list down
	//returns a value indicating list status
	//Will fail to insert if the list is full
	//

	uint8_t insert(T* pointer, uint8_t position)
	{
		T* localCopyVariable;
		T* loadedPointer;
		localCopyVariable = 0;
		loadedPointer = pointer;

		if (this->listFree_ < 1) //if the list isn't already full
		{
			return POINTER_stat_LISTFULL;
		}
		else
		{	//the list is not full yet
			if (this->get(position) != 0) //if there's something in that position of the list
			{
				if (position < LENGTH-1) //if we're not attempting an overflow
				{
					//for the whole list between LENGTH and 'position', shift everything down to accomodate the new pointer
					for (int i = position; i < (LENGTH); i++)
					{
						localCopyVariable = this->get(i); //copy the current contents of the target position
						this->list_[i] = loadedPointer;
						loadedPointer = localCopyVariable;
					}
					this->claimFromFree();
					return POINTER_stat_SUCCESS;
				}
				else
				{
					return POINTER_stat_FAILURE; //FAILURE
				}
			}
			else
			{	//there's nothing in that position of the list and it can be written
				this->list_[position] = pointer;
				return POINTER_stat_SUCCESS;
			}
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
			this->makeFree();
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
			this->makeFree();
		}
	}


	//
	//claimFromFree();
	//
	//adds to the 'stored' integer of the list, making one less in the 'free' count
	//

	void claimFromFree()
	{
		if (this->listFree_ > 0)
		{
			this->listFree_ --;
		}
	}


	//
	//makeFree()
	//

	void makeFree()
	{
		if (this->listFree_ < this->listSize_)
		{
			this->listFree_++;
		}
	}


	//
	//variables
	//

	uint8_t listSize_, iterator_, listFree_;
	T* list_[LENGTH];
};



#endif /* FOUNDATION_POINTERLISTKIT_H_ */
