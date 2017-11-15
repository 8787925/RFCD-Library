/*
 * J1939Message.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: Jimmy
 */

#include "Foundation\J1939Message.h"

//
//constructor
//

J1939Message::J1939Message(uint32_t pgn, uint8_t sa, uint8_t priority, CANhardware* network):CANMessage(network)
{
	pgn_ = pgn & 0x3FFFF;
	sa_ = sa & 0xFF;
	priority_ = priority & 0x07;
	messageData_.RTRenabled = true; 
	messageData_.messageDLC = 8; //testing, remove
	messageData_.direction = BOTH; //testing, remove
	this->updateIdentity();
}


//
//setPGN(uint32_t)
//

void J1939Message::setPGN(uint32_t pgn)
{
	pgn_ = pgn;
	this->updateIdentity();
}


//
//setSA(uint8_t)
//

void J1939Message::setSA(uint8_t sa)
{
	sa_ = sa;
	this->updateIdentity();
}


//
//setPriority(uint8_t)
//

void J1939Message::setPriority(uint8_t priority)
{
	priority_ = priority;
	this->updateIdentity();
}


//
//setPDUFormat(uint8_t)
//

void J1939Message::setPDUFormat(uint8_t pduFormat)
{
	pgn_ &= ~(uint32_t(0x0F)<<8);
	pgn_ |= (pduFormat<<8);
	this->updateIdentity();
}


//
//setPDUSpecific(uint8_t)
//

void J1939Message::setPDUSpecific(uint8_t pduSpecific)
{
	pgn_ &= ~(uint32_t(0x0F)<<0);
	pgn_ |= (pduSpecific<<0);
	this->updateIdentity();
}


//
//updateIdentity()
//

void J1939Message::updateIdentity()
{
	this->messageData_.Identity = priority_;
	this->messageData_.Identity = (this->messageData_.Identity << 18);
	this->messageData_.Identity |= pgn_;
	this->messageData_.Identity = (this->messageData_.Identity << 8); 
	this->messageData_.Identity |= sa_;
}
