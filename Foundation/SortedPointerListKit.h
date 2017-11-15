/*
 * SortedPointerList.h
 *
 *  Created on: Nov 9, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SORTEDPOINTERLISTKIT_H_
#define FOUNDATION_SORTEDPOINTERLISTKIT_H_


#include "PointerListKit.h"


template <const uint8_t LENGTH, class T_TYPE, class SORT_TYPE>

class SortedList
{
public:

	SortedList(bool isAscending)
	{
		isAscending_ = isAscending;
	}


	//
	//reSort()
	//
	//re-sorts the values in the list based on the current (referenced by pointer) values of 'PRIORITIES'
	//

	void reSort()
	{	bool isSorted = false;
		bool isInOrder = false;
		SORT_TYPE* sortValue = 0;
		T_TYPE* temporaryPointer = 0;

		int i = 0;  //looping variable for list interrogation

		while (!isSorted)
		{
			sortValue = priorityList_.get(i); //get the next value in the priority list
			isInOrder = false;

			if (isAscending_) //is the list ascending or descending
			{//the list is ascending
				for (int loopingList = i+1; loopingList < LENGTH; loopingList++) //loop between our value's position and the end of the list
				{
					if (*priorityList_.get(loopingList) < *sortValue) //if the next position in the loop is less than ours (meaning is out of order)
					{//the list is out of order

						temporaryPointer = pointerList_.get(i); //store the pointer value which is out of order

						pointerList_.remove(temporaryPointer);  //remove the out-of-order values from the list
						priorityList_.remove(sortValue);

						this->add(temporaryPointer, sortValue); //re-add the values into the list, and rely on the sort methods therein
						isInOrder = false;  					//assume that the positions of the list have all changed and re-interrogate from the beginning
						break;
					}
					//else just go to the next list position
				}
			}
			else
			{//the list is descending
				for (int loopingList = i+1; loopingList < LENGTH; loopingList++) //loop between our value's position and the end of the list
				{
					if (*priorityList_.get(loopingList) > *sortValue) //if the next position in the loop is greater than ours (meaning is out of order)
					{//the list is out of order

						temporaryPointer = pointerList_.get(i); //store the pointer value which is out of order

						pointerList_.remove(temporaryPointer);  //remove the out-of-order values from the list
						priorityList_.remove(sortValue);

						this->add(temporaryPointer, sortValue); //re-add the values into the list, and rely on the sort methods therein
						isInOrder = false;						//assume that the positions of the list have all changed and re-interrogate from the beginning
						break;
					}
					//else just go to the next list position
				}
			}

			//determine if we need to go to the next list position in sequence to determine in-order-ness or if we go back to the top of the list
			if (isInOrder)
			{//the list is indeed in order, so far, and hasn't been re-organized
				i++; //
			}
			else
			{//the list has had to be re-organized and has to be re-examined from the start of the list
				i=0;
			}

			//determine if we're finished with the re-sort
			if (i == LENGTH) //if the next list position is beyond the actual list (zero index)
			{// the list must have been sorted
				isSorted = true;
			}
		}

	}


	//
	//add(PointerType, PriorityType)
	//
	//WARNING: YOU MUST PROVIDE THE PRIORITY_TYPE WITH A NUMERICALLY
	//SORTABLE NUMBER, i.e. it must have a valid '<' and '>' operator
	//

	uint8_t add(T_TYPE* pointer, SORT_TYPE* sortBy)
	{
		uint8_t success = 0;

		if (pointerList_.free() > 0) //if there's room in the list
		{
			//is the list supposed to be ascending or descending?
			if (this->isAscending_)
			{
				//list is ascending
				success = this->insertAscendingList(pointer, sortBy);
			}
			else
			{
				//list is descending
				success = this->insertDescendingList(pointer, sortBy);
			}
		}
		else
		{	//there was no room in the list
			return POINTER_stat_LISTFULL;
		}

	}



private:
	//
	//insertAscendingList(T_TYPE, SORT_TYPE)
	//
	//inserts the handed pointer and priority into the list according to an ascending
	//pattern (index 0 = lowest position)
	//

	uint8_t insertAscendingList(T_TYPE* pointer, SORT_TYPE* sortBy)
	{
		uint8_t success = 0;

		for (int i = 0; i < LENGTH; i++)
		{
			if (*priorityList_.get(i) >= *sortBy || priorityList_.get(i) == 0)
			{
				//insert the value, because all the remainder of the list is greater than this value
				success = priorityList_.insert(sortBy, i);
				success &= pointerList_.insert(pointer, i);

				if (!success) //if either of the inserts failed
				{ // there was a failure of one or the other insertions, and both should be removed
					priorityList_.remove(sortBy);
					pointerList_.remove(pointer);
				}

				return success;
			}
		}

		return success; // if the program has reached this point, the initialized 0(fail) should return
	}


	//
	//insertDescendingList(T_TYPE*, SORT_TYPE*)
	//
	//inserts the handed pointer and priority into the list according to a descending
	//pattern (index 0 = highest value position)
	//

	uint8_t insertDescendingList(T_TYPE* pointer, SORT_TYPE* sortBy)
	{
		uint8_t success = 0;

		for (int i = 0; i < LENGTH; i++)
		{
			if ((*priorityList_.get(i) <= *sortBy) || (priorityList_.get(i) == 0)) //if the list value is less than the one we have, insert ours in that location and shift the list down
			{
				//insert the value, because all the remainder of the list is greater than this value
				success = priorityList_.insert(sortBy, i);
				success &= pointerList_.insert(pointer, i);

				if (!success) //if either of the inserts failed
				{ // there was a failure of one or the other insertions, and both should be removed
					priorityList_.remove(sortBy);
					pointerList_.remove(pointer);
				}

				return success;
			}
		}
	}


	//
	//variables
	//

	bool isAscending_;
	PointerList<T_TYPE, LENGTH> pointerList_, priorityList_;
};


#endif /* FOUNDATION_SORTEDPOINTERLISTKIT_H_ */
