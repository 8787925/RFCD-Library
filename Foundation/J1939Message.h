/*
 * J1939Message.h
 *
 *  Created on: Oct 14, 2016
 *      Author: Jimmy
 */

#ifndef J1939MESSAGE_H_
#define J1939MESSAGE_H_

#include "Foundation\CANMessage.h"
#include "Foundation\Thread.h" //DELETE THIS, TRIAL ONLY

class J1939Message: public CANMessage, public Thread
{public:

	void run(){this->send();}; //delete this trial only

	//
	//constructor
	//

	J1939Message(uint32_t pgn, uint8_t sa, uint8_t priority, CANhardware* network);


	//
	//setPGN(uint32_t)
	//

	void setPGN(uint32_t pgn);
	uint32_t getPGN(){return pgn_;};


	//
	//setSA(uint8_t)
	//

	void setSA(uint8_t sa);
	uint8_t getSA(){return sa_;};


	//
	//setPriority(uint8_t)
	//

	void setPriority(uint8_t priority);
	uint8_t getPriority(){return priority_;};


	//
	//setPDUFormat(uint8_t)
	//

	void setPDUFormat(uint8_t pduFormat);
	uint8_t getPDUFormat(){return (0x0F & (pgn_>>8));};


	//
	//setPDUSpecific(uint8_t)
	//

	void setPDUSpecific(uint8_t pduSpecific);
	uint8_t setPDUSpecific(){return (0x0F & pgn_);};


private:
	//
	//updateIdentity()
	//

	void updateIdentity();


	//
	//variables
	//

	uint8_t sa_;
	uint8_t da_;
	uint8_t priority_;
	uint32_t pgn_;
};



#endif /* J1939MESSAGE_H_ */
