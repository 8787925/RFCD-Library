/*
 * MatlabHeadder.h
 *
 *  Created on: Nov 11, 2016
 *      Author: Jimmy
 */

#ifndef MATLABHEADDER_H_
#define MATLABHEADDER_H_

#include "C:\Program Files (x86)\MATLAB\R2007b\extern\include\mex.h"

/* Input Arguments */

#define	T_IN	prhs[0]
#define	Y_IN	prhs[0]


/* Output Arguments */

#define	YP_OUT	plhs[0]




static void yprime(double output[],
				   double input[]  )
{
    //(void) t;     /* unused parameter */

    output[0] = 2*input[0] + input[1] + input[2] + input[3];

    return;
}

class ydoubleprime
{
	ydoubleprime() {};

	void add(double output[], double input[])
	{
		output[0] = 2*input[0] + input[1] + input[2] + input[3];
		return;
	};
};

void mexFunction( int nlhs, mxArray *plhs[],
				  int nrhs, const mxArray *prhs[] )

{
    double *output;
    double *t,*input;
    mwSize m,n;

    /* Check for proper number of arguments */

    if (nrhs != 2) {
	//mexErrMsgTxt("Two input arguments required.");
    } else if (nlhs > 1) {
	mexErrMsgTxt("Too many output arguments.");
    }

    /* Check the dimensions of Y.  Y can be 4 X 1 or 1 X 4. */

    m = mxGetM(Y_IN);//number of rows
    n = mxGetN(Y_IN);//number of columns

  /*  if (!mxIsDouble(Y_IN) || //double check to eliminate complex numbers and make sure we're using double's
    	 mxIsComplex(Y_IN) )//||
		 //(MAX(m,n) != 4) || (MIN(m,n) != 1))
    {
	mexErrMsgTxt("YPRIME requires that Y be a 4 x 1 vector of size 'double'.");
    }*/

    /* Create a matrix for the return argument */
    YP_OUT = mxCreateDoubleMatrix(m, n, mxREAL);

    /* Assign pointers to the various parameters */
    output = mxGetPr(YP_OUT);

    //t = mxGetPr(T_IN);
    input = mxGetPr(Y_IN);

    /* Do the actual computations in a subroutine */
    //yprime(output,input);
    ydoubleprime ydbp;
    ydbp.add(output, input);
    return;

}

#endif /* MATLABHEADDER_H_ */
