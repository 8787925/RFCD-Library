/*
 * CANMessage.h
 *
 *  Created on: Oct 11, 2016
 *      Author: Jimmy
 */

#ifndef CANMESSAGE_H_
#define CANMESSAGE_H_

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\CANdriver.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Listener.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\CANTypes.h"

class CANMessage: public Listener
{
public:

	//
	//CANmessage(networkID)
	//

	CANMessage(CANhardware* network);


	//
	//setIdentifier(uint32)
	//

	void setIdentifier(uint32_t identifier);
	uint32_t getIdentifier(){return messageData_.Identity;};


	//
	//send()
	//

	void send();


	//
	//onListenerEvent()
	//

	void listenerEvent();


	//
	//onReceive()
	//

	virtual void onReceive(){return;};


	//
	//sendRTR(uint8_t)
	//

	void sendRTR();
	
	
	//
	//addSelf()
	//
	
	void addSelf();


	//
	//Variables
	//
	canPack messageData_;
	CANhardware* network_;

};



#endif /* CANMESSAGE_H_ */
