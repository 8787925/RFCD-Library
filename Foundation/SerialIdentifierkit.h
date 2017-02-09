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

	SerialIdentifier()
	{

	}


	//
	//compare(uint8_t*, uint8_t length)
	//

	bool compare(uint8_t* externalIdent, uint8_t length)
	{
		if (BYTES > length)
		{
			//examine only the first part of BYTES
		}
		else
		{
			//examine only the first part of externalident
		}
	}

private:
	//
	//variables
	//

	uint8_t identifier_[BYTES];

};


#endif /* FOUNDATION_SERIALIDENTIFIERKIT_H_ */
