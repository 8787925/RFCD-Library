/*
 * SerialIdentifierkit.h
 *
 *  Created on: Feb 8, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SERIALIDENTIFIERKIT_H_
#define FOUNDATION_SERIALIDENTIFIERKIT_H_

#include "Foundation\DataRequest.h"
#include "Foundation\Listener.h"

enum txOrRx
{
	serial_TXonly,
	serial_RXonly,
	serial_BOTH
};

enum serialPayloadType
{
	ASCII,
	BINARY
};

template <const uint8_t BYTES>

class SerialIdentifier: virtual public DataRequest, virtual public Listener
{
public:
	//
	//constructor
	//

	SerialIdentifier(uint8_t* identity, serialPayloadType payloadType, uint8_t arg)
	{
		if (payloadType == ASCII)
		{
			terminator_ = arg;
			payloadSize_ = 0;
		}
		else
		{
			terminator_ = 255;
			payloadSize_ = arg;
		}

		payloadType_ = payloadType;

		for (int i = 0; i<BYTES; i++)
		{
			identifier_[i] = identity[i];
		}
	}


	//
	//getTerminator()
	//

	uint8_t getTerminator()
	{
		return terminator_;
	}

	void setTerminator(uint8_t terminator)
	{
		terminator_ = terminator;
	}


	//
	//getPayloadSize()
	//

	uint8_t getPayloadSize()
	{
		return payloadSize_;
	}


	//
	//getPayloadType()
	//

	serialPayloadType getPayloadType()
	{
		return payloadType_;
	}

	void setPayloadType(serialPayloadType type)
	{
		payloadType_ = type;

		if (type == ASCII)
		{
			payloadSize_ = 0;
		}
		else
		{
			terminator_ = 255;
		}
	}


	//
	//compare(uint8_t*, uint8_t length)
	//

	bool compare(uint8_t* externalIdent, uint8_t length)
	{
		if (BYTES > length) //locally there is more text to compare than is being given
		{
			for (int i = 0; i<length; i++)
			{
				if (externalIdent[i] != identifier_[i])
				{
					return false;
				}
			}

			return true;
			//examine only the first part of BYTES
		}
		else
		{
			for (int i = 0; i<BYTES; i++)
			{
				if (externalIdent[i] != identifier_[i])
				{
					return false;
				}
			}

			return true;
			//examine only the first part of externalident
		}
	}


	//
	//setIdentifier(uint8_t [BYTES])
	//

	void setIdentifier(uint8_t *identifier)
	{
		for (int i = 0; i<BYTES; i++)
		{
			identifier_[i] = identifier[i];
		}
	}


	uint8_t* getIdentifier()
	{
		return &identifier_[0];
	}


	//
	//getIdLength()
	//

	uint8_t getIdLength()
	{
		return BYTES;
	}

private:
	//
	//variables
	//

	uint8_t identifier_[BYTES];
	uint8_t payloadSize_;
	uint8_t terminator_;
	serialPayloadType payloadType_;

};


#endif /* FOUNDATION_SERIALIDENTIFIERKIT_H_ */
