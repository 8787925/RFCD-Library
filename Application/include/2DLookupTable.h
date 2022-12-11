/*
 * 2DLookupTable.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Jimmy
 */

#ifndef APPLICATION_2DLOOKUPTABLE_H_
#define APPLICATION_2DLOOKUPTABLE_H_

#include "Foundation\BiLinearInterpolation.h"

template <const uint8_t Rows, const uint8_t Columns, class IndexType, class TableType, class ReturnType>

class LookupTable_2D: private BiLinearInterpolation<IndexType, TableType, ReturnType>
{public:
	//
	//constructor
	//

	LookupTable_2D()
	{
		sequentialLoadRow_ = 0;
		sequentialLoadColumn_ = 0;
		for (int i=0; i<Rows; i++)
		{
			rowsIndex_[i] = 0;
			for (int n=0; n<Columns; n++)
			{
				table_[i][n] = 0; //load zeros into the table
				columnsIndex_[n] = 0;
			}
		}
	};


	//
	//lookup(X,Y)
	//

	ReturnType lookup(IndexType columnsValue, IndexType rowsValue)
	{
		//return the lookup, interpolated
		IndexType columnIndicies [2];
		IndexType rowIndicies [2];
		uint8_t rowIndicies_idx [2];
		uint8_t columnIndices_idx [2];
		TableType tableValues [2][2];

		///Discover rows above and below the given column value
		for (uint8_t i = (Columns-1); i>=0; i--)
		{
			if (i==0)
			{
				columnIndicies[0] = columnsIndex_[0];
				columnIndices_idx[0] = 0;
				break;
			}
			if (columnsIndex_[i] <= columnsValue)
			{
				columnIndicies[0] = columnsIndex_[i];
				columnIndices_idx[0] = i;
				break;
			}
		}

		for (uint8_t i = 0; i<Columns; i++)
		{
			if (i==(Columns-1))
			{
				columnIndicies[1] = columnsIndex_[(Columns-1)];
				columnIndices_idx[1] = Columns - 1;
				break;
			}
			if (columnsIndex_[i] >= columnsValue)
			{
				columnIndicies[1] = columnsIndex_[i];
				columnIndices_idx[1] = i;
				break;
			}
		}

		//Discover rows above and below the given row value
		for (uint8_t i = (Rows-1); i>=0; i--)
		{
			if (i==0)
			{
				rowIndicies[0] = rowsIndex_[0];
				rowIndicies_idx[0] = 0;
				break;
			}
			if (rowsIndex_[i] <= rowsValue)
			{
				rowIndicies[0] = rowsIndex_[i];
				rowIndicies_idx[0] = i;
				break;
			}
		}

		for (uint8_t i = 0; i<Rows; i++)
		{
			if (i==(Rows-1))
			{
				rowIndicies[1] = rowsIndex_[(Rows-1)];
				rowIndicies_idx[1] = Rows - 1;
				break;
			}
			if (rowsIndex_[i] >= rowsValue)
			{
				rowIndicies[1] = rowsIndex_[i];
				rowIndicies_idx[1] = i;
				break;
			}
		}

		//get the table values at those index locations
		tableValues[0][0] = table_[rowIndicies_idx[0]][columnIndices_idx[0]];
		tableValues[1][0] = table_[rowIndicies_idx[1]][columnIndices_idx[0]];
		tableValues[0][1] = table_[rowIndicies_idx[0]][columnIndices_idx[1]];
		tableValues[1][1] = table_[rowIndicies_idx[1]][columnIndices_idx[1]];

#if 0
		cout << '\n' << "Columns";
		cout << '\n' << columnIndicies[0] << " " << columnIndicies[1];
		cout << '\n' << "Rows";
		cout << '\n' << rowIndicies[0] << " " << rowIndicies[1];
		cout << '\n' << "Table Entries";
		cout << '\n' << tableValues [0][0] << " " << tableValues[0][1] << " " << tableValues[1][0] << " " << tableValues[1][1];
#endif
		return this->interpolate2D(columnsValue, rowsValue,
									columnIndicies[0],
									rowIndicies[0],
									columnIndicies[1],
									rowIndicies[1],
									tableValues[0][0],
									tableValues[1][0],
									tableValues[0][1],
									tableValues[1][1]);

	};


	//
	//loadSequentialy(TableType)
	//

	void loadSequentially(TableType Value)
	{
		if ((sequentialLoadColumn_ < Columns) && (sequentialLoadRow_ < Rows))
		{
			table_[sequentialLoadRow_][sequentialLoadColumn_] = Value;
		}

		sequentialLoadColumn_++;
		if (sequentialLoadColumn_ >= Columns)
		{
			sequentialLoadColumn_ = 0;
			sequentialLoadRow_ ++;
		}
	};


	//
	//variables
	//
	IndexType columnsIndex_[Columns];
	IndexType rowsIndex_[Rows];

private:
	//
	//variables
	//

	TableType table_[Rows][Columns];
	uint16_t sequentialLoadRow_, sequentialLoadColumn_;


};

#endif /* APPLICATION_2DLOOKUPTABLE_H_ */
