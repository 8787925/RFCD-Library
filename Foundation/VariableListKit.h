/*
 * VariableListKit.h
 *
 *  Created on: Mar 15, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_VARIABLELISTKIT_H_
#define FOUNDATION_VARIABLELISTKIT_H_


template <const uint8_t LENGTH, class T>

class VariableList
{
public:
	//
	//constructor
	//

	VariableList(T initialValue)
	{
		this->copyToAll(initialValue);
		listFree_ = 0;
		itterator_ = 0;
		listSize_ = LENGTH;
	}


	//
	//copyToAll(T)
	//

	void copyToAll(T value)
	{
		for (int i=0; i<LENGTH; i++)
		{
			list_[i] = value;
		}
	}


	//
	//size()
	//

	uint8_t size()
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
	//addToPosition(T, uint8_t)
	//

	bool addToPosition(T value, uint8_t position)
	{
		bool success = false;

		if (position < LENGTH)
		{

			list_[position] = value;
			success = true;
		}

		return success;
	}


	//
	//insertAtTop(T)
	//

	bool insertAtTop(T value)
	{
		bool success = false;

		this->roundRobinDown();
		success = this->addToPosition(value, 0);

		return success;
	}


	//
	//insertAtBottom(T)
	//

	bool insertAtBottom(T value)
	{
		bool success = false;

		this->roundRobinUp();
		success = this->addToPosition(value, (LENGTH-1));

		return success;
	}


	//
	//itterate(bool* )
	//

	T itterate(bool* newLoop)
	{
		if (*newLoop)
		{
			itterator_ = 0;
			*newLoop = false;
		}

		if ((itterator_ < LENGTH) && (this->listFree_ == 0))
		{
			return list_[itterator_];
		}

		return 0;
	}


	//
	//get(uint8)
	//

	T get(uint8_t position)
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
	//getPointer()
	//

	T* getPointer()
	{
		return &list_[0];
	}


private:

	//
	//roundRobinDown()
	//

	void roundRobinDown()
	{
		T temp = list_[LENGTH-1];

		this->deleteShiftDown(LENGTH-1);
		this->addToPosition(temp, 0);
	}


	//
	//roundRobinUp()
	//

	void roundRobinUp()
	{
		T temp = list_[0];
		this->deleteShiftUp(0);
		this->addToPosition(temp, (LENGTH-1));
	}


	//
	//deleteShiftUp(uint8_t)
	//
	//removes the entry indicated and shifts the list upward, inserting 0 at the end

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
					//&list_[i] = 0;
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
					//list_[i] = 0;
				}
			}
		}
	}


	//
	//variables
	//

	uint8_t listSize_, itterator_, listFree_;
	T list_[LENGTH];
};


#endif /* FOUNDATION_VARIABLELISTKIT_H_ */
