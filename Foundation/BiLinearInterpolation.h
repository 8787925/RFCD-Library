/*
 * BiLinearInterpolation.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_BILINEARINTERPOLATION_H_
#define FOUNDATION_BILINEARINTERPOLATION_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\LinearInterpolation.h"

template <class IndexType, class TableType, class ReturnType>
class BiLinearInterpolation: protected LinearInterpolation<IndexType, TableType, ReturnType>
{public:
	//
	//constructor
	//

	BiLinearInterpolation(){};


	//
	//interpolate2D(IndexType, IndexType, IndexType, TableType, IndexType,...)
	//

	ReturnType interpolate2D(IndexType X, IndexType Y,
							IndexType X0, IndexType X1, IndexType Y0, IndexType Y1,
							TableType Z_X0Y0, TableType Z_X0Y1, TableType Z_X1Y0, TableType Z_X1Y1)
	{
		ReturnType R0, R1;

		R0 = this->LinearInterpolation.interpolate(ReturnType(X), X0, Z_X0Y0, X1, Z_X1Y0); //interpolate on Y0 line
		R1 = this->LinearInterpolation.interpolate(ReturnType(X), X0, Z_X0Y1, X1, Z_X1Y1); //interpolate on Y1 line

		return this->BiLinearInterpolation.interpolate(Y, Y0, R0, Y1, R1);
	}
	
		
		
	//
	//interpolate(IndexType, TableType, IndexType, TableType)
	//

	ReturnType interpolate(ReturnType X, IndexType X1, ReturnType Y1, IndexType X2, ReturnType Y2)
	{
		if (X1 == X2)
		{
			return ReturnType(Y1);
		}
		ReturnType denominator = ReturnType(X2)-ReturnType(X1);
		ReturnType numerator = (ReturnType(X) - ReturnType(X1))*(ReturnType(Y2)-ReturnType(Y1));
		return ReturnType(Y1) + (numerator / denominator);
	}

};

#endif /* FOUNDATION_BILINEARINTERPOLATION_H_ */
