/*
 * SerialKit.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Jimmy
 */

//#include "Config.h"

#ifndef FOUNDATION_SERIALMESSAGEKIT_H_
#define FOUNDATION_SERIALMESSAGEKIT_H_

#include "Foundation\DataPayloadKit.h"
#include "Foundation\SerialIdentifierkit.h"
#include "Foundation\Listener.h"

#ifndef MAX_SERIAL_DEVICE_MESSAGES
#define MAX_SERIAL_DEVICE_MESSAGES 10
#endif

#ifndef SERIAL_IDENTIFIER_LENGTH
#define SERIAL_IDENTIFIER_LENGTH 5
#endif




template <const uint8_t LENGTH, const uint8_t IDENTITYLENGTH>

class SerialMessage: public SerialIdentifier<IDENTITYLENGTH>, public DataPayload<LENGTH>
{
public:

	//
	//constructor
	//

	SerialMessage(txOrRx direction, uint8_t *identity, serialPayloadType payloadType, uint8_t terminatorOrLength) :
		SerialIdentifier<IDENTITYLENGTH>(identity, payloadType, terminatorOrLength),
		DataPayload<LENGTH>(0xFF)
	{
		messageDirection_ = direction;
		sending_ = false;
		recieving_ = false;
		if ((direction == serial_RXonly) || (direction == serial_BOTH))
		{
			this->enableRecieve();
		}
	}


	//
	//send()
	//

	virtual void send()
	{
		return;
	}


	//
	//enableRecieve()
	//

	virtual void enableRecieve()
	{
		return;
	}


	//
	//disableRecieve()
	//

	virtual void disableRecieve()
	{
		return;
	}


	//
	//getMessageLength()
	//

	uint8_t getMessageLength()
	{
		return LENGTH;
	}


	//
	//virtual onListener()
	//

	virtual void listenerEvent()
	{
		return;
	}


private:
	//
	//variables
	//

	bool sending_, recieving_;
	txOrRx messageDirection_;
};


#endif /* FOUNDATION_SERIALMESSAGEKIT_H_ */
