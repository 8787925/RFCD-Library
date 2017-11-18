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
	//setOrientation(bool)
	//

	void setOrientation(bool isAscending)
	{
		isAscending_ = isAscending;
		this->reSort();
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

		//THIS METHOD ASSUMES THAT ALL LISTS ARE PACKED TOP DOWN, NO NULL POINTERS CAN EXIST IN THE MIDDLE OF A LIST -
		//WHICH SHOULD BE GUARANTEED BY THE remove() METHOD
		//
		//Method compares two adjacent values to check each pair for correct order, for LENGTH times
		//relying on the 'insert' method to correctly sort a re-inserted value which was found to be out of order

		int i = 0;  //looping variable for list interrogation

		while (!isSorted)
		{
			sortValue = priorityList_.get(i); //get the current value in the list at the position
			isInOrder = true; //is set false if an adjacent pair is found to be out of order

			if ((sortValue != 0) && (i < LENGTH)) //if there's not a null pointer
			{
				if (isAscending_) //is the list ascending or descending
				{//the list is ascending

					if ((priorityList_.get(i+1) != 0) && (*priorityList_.get(i+1) < *sortValue)) //if the next position in the loop is less than ours (meaning is out of order) AND if the next value is not NULL
					{//the list is out of order, swap the positions of the two pointers

						temporaryPointer = pointerList_.get(i); //store the pointer value which is out of order, sort value is already saved

						pointerList_.remove(temporaryPointer);  //remove the out-of-order values from the list
						priorityList_.remove(sortValue);

						this->add(temporaryPointer, sortValue); //re-add the values into the list, and rely on the sort methods therein
						isInOrder = false;  					//assume that the positions of the list have all changed and re-interrogate from the beginning
					}
					//else just go to the next list position
				}
				else
				{//the list is descending

						if ((priorityList_.get(i+1) != 0) && (*priorityList_.get(i+1) > *sortValue)) //if the next position in the loop is greater than ours (meaning is out of order)
						{//the list is out of order

							temporaryPointer = pointerList_.get(i); //store the pointer value which is out of order, sort value is already saved

							pointerList_.remove(temporaryPointer);  //remove the out-of-order values from the list
							priorityList_.remove(sortValue);

							this->add(temporaryPointer, sortValue); //re-add the values into the list, and rely on the sort methods therein
							isInOrder = false;						//assume that the positions of the list have all changed and re-interrogate from the beginning
						}
				}
			}//null pointer check

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
			if (i >= LENGTH) //if the next list position is beyond the actual list (zero index)
			{// the list must have been sorted
				isSorted = true;
			}
		}

		return;

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
			success = POINTER_stat_LISTFULL;
		}

		return success;
	}


	//
	//get(uint)
	//

	T_TYPE* get(uint8_t position)
	{
		if (position < LENGTH)
		{
			return pointerList_.get(position);
		}
		else
		{
			return 0;
		}
	}


	//
	//getPriority(T_Type)
	//
	//returns the priority of the pointer given, if available
	//

	SORT_TYPE getPriority(T_TYPE* pointer)
	{
		SORT_TYPE returnValue = -1; //initialize to fault condition return

		if (pointer != 0) //if we were given a valid pointer
		{
			 returnValue = *getPriorityPointer(pointer); //return the dereferenced priority pointer
		}

		return returnValue;
	}


	//
	//remove(T_Type)
	//remove(Sort_Type)
	//
	//removes the entry and its priority pair
	//

	uint8_t remove(T_TYPE* pointer)
	{
		if (pointer ==0)
		{
			return 0;
		}

		SORT_TYPE* priorityPointer = 0; //temporary pointer for the position of the priority associated with the given 'pointer'
		uint8_t success = 0;

		priorityPointer = this->getPriorityPointer(pointer);

		if (priorityPointer != 0) //if the priority was found
		{
			success |= priorityList_.remove(priorityPointer);
			success |= pointerList_.remove(pointer);			//this method will return 'success' if EITHER of the pointers is removed, but because it depends on discovering both in list it shouldn't be possible to have a partial success anyhow
		}

		return success;
	}

private:
	//
	//getPriority(T_Type)
	//
	//returns the priority pointer pair for a given list pointer
	//

	SORT_TYPE* getPriorityPointer(T_TYPE* pointer)
	{
		SORT_TYPE* returnValue = 0; //initialize to fault condition return

		if (pointer != 0) //if we were given a valid pointer
		{
			for (int i = 0; i < LENGTH; i++) //for potentially the whole length of the list
			{
				if (this->get(i) == pointer) //if the pointer list result matches what we were given
				{
					returnValue = priorityList_.get(i); //return the priority pointer
					break;
				}
			}
		}

		return returnValue;
	}


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
			if (priorityList_.get(i) == 0 || *priorityList_.get(i) >= *sortBy) //scalar 'or' prevents the use of .get() and a null return from get()
			{
				//insert the value, because all the remainder of the list is greater than this value
				success = priorityList_.insert(sortBy, i);
				success &= pointerList_.insert(pointer, i);

				if (!(success & POINTER_stat_SUCCESS)) //if either of the inserts failed
				{ // there was a failure of one or the other insertions, and both should be removed
					priorityList_.remove(sortBy);
					pointerList_.remove(pointer);
				}

				break;
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
			if ((priorityList_.get(i) == 0) || (*priorityList_.get(i) <= *sortBy)) //if the list value is less than the one we have, insert ours in that location and shift the list down
			{
				//insert the value, because all the remainder of the list is greater than this value
				success = priorityList_.insert(sortBy, i);
				success &= pointerList_.insert(pointer, i);

				if (!(success & POINTER_stat_SUCCESS)) //if either of the inserts failed
				{ // there was a failure of one or the other insertions, and both should be removed
					priorityList_.remove(sortBy);
					pointerList_.remove(pointer);
				}

				break;
			}
		}

		return success;
	}


	//
	//variables
	//

	bool isAscending_;
	PointerList<T_TYPE, LENGTH> pointerList_;
	PointerList<SORT_TYPE, LENGTH> priorityList_;

};


#endif /* FOUNDATION_SORTEDPOINTERLISTKIT_H_ */
