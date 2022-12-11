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
public:

	DataRequest()
	{
		pushBytePosition_ = 0;
		pullBytePosition_ = 0;
	}
	//virtual uint8_t onByteRequest(bool* endOfStream) ;

	virtual uint8_t onPullByte(bool* endOfStream) = 0;

	virtual void onPushByte(uint8_t push, bool* newStream) = 0;

	//virtual void onPushComplete() = 0;

	uint8_t pushBytePosition_;
	uint8_t pullBytePosition_;
};

#endif /* FOUNDATION_DATAREQUEST_H_ */
