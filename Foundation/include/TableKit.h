/*
 * TableKit.h
 *
 *  Created on: Feb 14, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_TABLEKIT_H_
#define FOUNDATION_TABLEKIT_H_

//keep a table full of things that could be of two different types

#include "PointerList.h"

template <class TYPEX, class TYPEY, const uint8_t LENGTH>

class Table
{
	//
	//constructor
	//

	Table ()
	{

	}


	//
	//returnPair(TYPEX)
	//

	TYPEY* returnPair(TYPEX* columnOneValue)
	{

		if (columnOneValue == 0)
		{
			return 0;
		}

		for (int i = 0; i<LENGTH; i++)
		{
			if (columnOne_.get(i) == columnOneValue)
			{
				return columnTwo_.get(i);
			}
		}

		return 0;
	}

private:
	//
	//variables
	//

	PointerList<TYPEX, LENGTH> columnOne_;
	PointerList<TYPEY, LENGTH> columnTwo_;
};



#endif /* FOUNDATION_TABLEKIT_H_ */
