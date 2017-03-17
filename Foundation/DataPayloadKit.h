/*
 * DataPayload.h
 *
 *  Created on: Mar 16, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_DATAPAYLOADKIT_H_
#define FOUNDATION_DATAPAYLOADKIT_H_

#include "Foundation/DataRequest.h"

template <const uint8_t LENGTH>

class DataPayload: virtual public DataRequest
{
public:
	//
	//constructor
	//

	DataPayload (uint8_t initialValue)
	{
		for (uint8_t i = 0; i<LENGTH; i++)
		{
			messageBytes_[i] =  initialValue;
		}
	}


	//
	//onPullByte() -> DataRequest
	//

	uint8_t onPullByte(bool* endOfStream)
	{
		if (*endOfStream)
		{
			this->pullBytePosition_ = 0;
			*endOfStream = false;
		}

		uint8_t data = this->messageBytes_[this->pullBytePosition_];

		if (this->pullBytePosition_ >= LENGTH)
		{
			//remove the message from queue, somehow it got missed
			*endOfStream = true; //TODO: assumes that the first in the TX queue is this message
			return 0;
		}
		else
		{
			//continue to send message bytes

			//check to see if this message should be removed
			if (this->pullBytePosition_ == (LENGTH-1)) //if this is the last byte of the message to be sent
			{
				*endOfStream = true;
			}

			this->pullBytePosition_ ++;
			return data;
		}
	}


	//
	//onPushByte(uint8_t) ->DataRequest
	//

	void onPushByte(uint8_t data, bool* newStream)
	{
		if (*newStream)
		{
			this->pushBytePosition_ = 0;
			*newStream = false;
		}

		if (this->pushBytePosition_ < LENGTH)
		{
			//continue to allow insertion of bytes
			this->messageBytes_[this->pushBytePosition_] = data;
			this->pushBytePosition_ ++;
		}
		else
		{
			//do nothing
			return;
		}
	}


private:
	//
	//variables
	//

	uint8_t messageBytes_[LENGTH];
};

#endif /* FOUNDATION_DATAPAYLOADKIT_H_ */
