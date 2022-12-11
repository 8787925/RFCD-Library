/*
 * SerialManager.h
 *
 *  Created on: Feb 9, 2017
 *      Author: mattb
 */

#ifndef FOUNDATION_SERIALMANAGER_H_
#define FOUNDATION_SERIALMANAGER_H_

#include "PointerListKit.h"

template <class TYPE, const uint8_t LISTLENGTH>

class SerialManager
{
public:
	//
	//instance
	//

	SerialManager* instance()
	{
		static SerialManager TheSerialManager(void);
		return &TheSerialManager;
	}

private:

	//
	//constructor
	//

	SerialManager()
	{

	}

};


#endif /* FOUNDATION_SERIALMANAGER_H_ */
