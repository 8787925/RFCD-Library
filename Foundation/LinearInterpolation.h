/*
 * LinearInterpolation.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Jimmy
 */

#ifndef FOUNDATION_LINEARINTERPOLATION_H_
#define FOUNDATION_LINEARINTERPOLATION_H_


template <class IndexType, class TableType, class ReturnType>

class LinearInterpolation
{public:
	//
	//constructor
	//

	LinearInterpolation(){;};


	//
	//interpolate(IndexType, TableType, IndexType, TableType)
	//

	ReturnType interpolate(ReturnType X, IndexType X1, TableType Y1, IndexType X2, TableType Y2)
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


#endif /* FOUNDATION_LINEARINTERPOLATION_H_ */
