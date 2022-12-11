/*
 * CANMessage.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: Jimmy
 */

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\CANMessage.h"


//
//constructor
//

CANMessage::CANMessage(CANhardware* network)
{
	network_ = network;
	messageData_.FULL64BITrxFIELD = UINT64_MAX;
	messageData_.FULL64BITtxFIELD = UINT64_MAX;
	messageData_.mobSerialNumber = 0xFF;
}


//
//setIdentifier(uint32)
//

void CANMessage::setIdentifier(uint32_t identifier)
{
	messageData_.Identity = identifier;
}


//
//send()
//

void CANMessage::send()
{
	network_->send(&this->messageData_);
}


//
//sendRTR()
//

void CANMessage::sendRTR()
{
	network_->sendRTR(&messageData_);
}


//
//addSelf()
//
	
void CANMessage::addSelf()
{
	network_->add(this,&messageData_);
}

//
//listenerEvent
//

void CANMessage::listenerEvent()
{	//PORTB ^= (1<<PINB6);
	//messageData_.FULL64BITtxFIELD=messageData_.FULL64BITrxFIELD;
	this->onReceive();
}
