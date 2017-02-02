/*
 * ListKit.h
 *
 *  Created on: Jan 22, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_POINTERLISTKIT_H_
#define FOUNDATION_POINTERLISTKIT_H_


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
		itterator_ = 0;
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
	//itterate()
	//

	T* itterate()
	{
		itterator_ ++;
		if (itterator_ == LENGTH)
		{
			itterator_ = 1;
		}
		return list_[itterator_-1];
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

	uint8_t listSize_, itterator_, listFree_;
	T* list_[LENGTH];
};



#endif /* FOUNDATION_POINTERLISTKIT_H_ */
