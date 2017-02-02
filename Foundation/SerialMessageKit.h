/*
 * SerialKit.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_SERIALMESSAGEKIT_H_
#define FOUNDATION_SERIALMESSAGEKIT_H_

#include "DataRequest.h"
#include "Listener.h"

#ifndef MAX_SERIAL_DEVICE_MESSAGES
#define MAX_SERIAL_DEVICE_MESSAGES 10
#endif

template <const uint8_t LENGTH>

class SerialMessage: public Listener, public DataRequest
{
public:

	//
	//constructor
	//

	SerialMessage(SerialDevice <MAX_SERIAL_DEVICE_MESSAGES>* serialNetwork)
	{
		serialNetwork_ = serialNetwork;

		for (int i=0; i<LENGTH; i++)
		{
			messageBytes_[i] = 0;
		}

		sendIndex_ = 0;
		sending_ = false;
	}


	//
	//send()
	//

	void send()
	{
		if (!sending_)
		{
			sendIndex_ = 0;
			sending_ = true;
			serialNetwork_->startStream(this);
		}
	}


	//
	//onByteRequest()
	//

	uint8_t onPullByte()
	{
		if ((sending_) && (sendIndex_ < LENGTH))
		{
			return messageBytes_[sendIndex_];
			sendIndex_++;
			if (sendIndex_>= LENGTH)
			{
				serialNetwork_->finishedStream(this);
			}
		}
		else
		{
			serialNetwork_->finishedStream(this);
			return 0;
		}
	}

private:

	//
	//variables
	//

	SerialDevice <MAX_SERIAL_DEVICE_MESSAGES>* serialNetwork_;
	uint8_t messageBytes_[LENGTH];
	uint8_t sendIndex_;
	bool sending_;

};


#endif /* FOUNDATION_SERIALMESSAGEKIT_H_ */
