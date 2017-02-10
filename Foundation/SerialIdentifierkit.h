/*
 * SerialIdentifierkit.h
 *
 *  Created on: Feb 8, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SERIALIDENTIFIERKIT_H_
#define FOUNDATION_SERIALIDENTIFIERKIT_H_


template <const uint8_t BYTES>

class SerialIdentifier
{
public:
	//
	//constructor
	//

	SerialIdentifier(uint8_t identity[BYTES])
	{
		for (int i = 0; i<BYTES; i++)
		{
			identifier_[i] = identity[i];
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
				if (*externalIdent[i] != identifier_[i])
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
				if (*externalIdent[i] != identifier_[i])
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

	void setIdentifier(uint8_t identifier[BYTES])
	{
		for (int i = 0; i<BYTES; i++)
		{
			identifier_[i] = identifier[i];
		}
	}


	uint8_t* getIdentifier()
	{
		return &identifier_;
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

};


#endif /* FOUNDATION_SERIALIDENTIFIERKIT_H_ */
