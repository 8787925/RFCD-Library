/*
 * DataRequest.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_DATAREQUEST_H_
#define FOUNDATION_DATAREQUEST_H_



class DataRequest
{
	virtual uint8_t onByteRequest() = 0;

	virtual uint8_t onPullByte() = 0;

	virtual void onPushByte(uint8_t push) = 0;
};

/*
class pushByte
{
	virtual void onPushByte(uint8_t push) = 0;
};


class pullByte
{
	virtual uint8_t onPullByte() = 0;
};
*/

#endif /* FOUNDATION_DATAREQUEST_H_ */
