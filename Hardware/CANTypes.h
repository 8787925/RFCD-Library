/*
 * CANTypes.h
 *
 *  Created on: Oct 11, 2016
 *      Author: Jimmy
 */

#ifndef CANTYPES_H_
#define CANTYPES_H_

//
//type definitions
//

enum TXorRX{NEITHER = 0,
			TX = 1,
		    RX = 2,
			BOTH = 3};

enum MOBspot{	mob0,
				mob1,
				mob2,
				mob3,
				mob4,
				mob5};
//
//canPack
//contains the full message both in rx and tx for a given object/message

struct canPack
	{
		uint64_t FULL64BITtxFIELD; //Right justified for any given DLC packed with 0xF's
		uint64_t FULL64BITrxFIELD; //Right justified for any given DLC packed with 0xF's
		uint8_t messageDLC;
		uint32_t Identity;
		uint8_t timeStampL;
		uint8_t timeStampH;
		TXorRX direction;
		bool RTRenabled;
		uint8_t mobSerialNumber;
	};




#endif /* CANTYPES_H_ */
