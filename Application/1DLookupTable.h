/*
 * 1DLookupTable.h
 *
 *  Created on: Nov 17, 2016
 *      Author: Jimmy
 */

#ifndef APPLICATION_1DLOOKUPTABLE_H_
#define APPLICATION_1DLOOKUPTABLE_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\LinearInterpolation.h"


template <const uint8_t Indecies, class IndexType, class TableType, class ReturnType>

class LookupTable_1D: private LinearInterpolation<IndexType, TableType, ReturnType>
{public:

	//
	//constructor
	//

	LookupTable_1D()
	{
		for (uint8_t i=0; i<Indecies; i++)
		{
			table_[i] = 0;
			index_[i] = 0;
		}
		serialLoad_idx = 0;
	};


	//
	//lookup (indexType)
	//

	ReturnType lookup(IndexType value)
	{
		//return the lookup, interpolated
		IndexType indexValues [2];
		uint8_t indexValues_idx [2];
		TableType tableValues [2];

		///Discover index above and below the given value
		for (uint8_t i = (Indecies-1); i>=0; i--) //for i=2 to 0, counting down
		{
			if (i==0)
			{
				indexValues[0] = index_[0];
				indexValues_idx[0] = 0;
				break;
			}
			if (index_[i] <= value)
			{
				indexValues[0] = index_[i];
				indexValues_idx[0] = i;
				break;
			}
		}

		for (uint8_t i = 0; i<Indecies; i++)
		{
			if (i==(Indecies-1))
			{
				indexValues[1] = index_[(Indecies-1)];
				indexValues_idx[1] = Indecies - 1;
				break;
			}
			if (index_[i] >= value)
			{
				indexValues[1] = index_[i];
				indexValues_idx[1] = i;
				break;
			}
		}

		tableValues [0] = table_[indexValues_idx[0]];
		tableValues [1] = table_[indexValues_idx[1]];

#if 0
		cout << "TableValue 0 " << tableValues [0];
		cout <<  '\n';
		printf( "%6.4lf", tableValues [0] );
		cout << '\n';
		cout << "TableValue 1 " << tableValues [1] ;
		cout <<  '\n';
		printf( "%6.4lf", tableValues [1] );
		cout << '\n';
		cout << "IndexValue 0 " <<  indexValues [0];
		cout <<  '\n';
		printf( "%6.4lf", indexValues [0] );
		cout << '\n';
		cout << "IndexValue 1 " << indexValues [1] ;
		cout <<  '\n';
		printf( "%6.4lf", indexValues [1] );
		cout << '\n';
		cout << "ReturnValue " << ReturnType(value);
		cout <<  '\n';
		printf( "%6.4lf", ReturnType(value) );
		cout << '\n';
#endif
		return this->interpolate(ReturnType(value), indexValues[0], tableValues[0], indexValues[1], tableValues[1]);
	}


	//
	//transfer (IndexType)
	//

	ReturnType transfer (IndexType value)
	{
		return this->lookup(value);
	}


	//
	//loadSerial(IndexType, TableType)
	//

	void loadSerial(IndexType IndexValue, TableType TableValue)
	{
		if (serialLoad_idx < Indecies)
		{
			table_[serialLoad_idx] = TableValue;
			index_[serialLoad_idx] = IndexValue;
		}

		serialLoad_idx ++;
	}


private:
	//
	//variables
	//

	IndexType index_[Indecies];
	TableType table_[Indecies];
	uint8_t serialLoad_idx;


};


#endif /* APPLICATION_1DLOOKUPTABLE_H_ */
