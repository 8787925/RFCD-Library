/*
 * CANdriver.cpp
 *
 *  Created on: Oct 7, 2016
 *      Author: Jimmy
 */

#include "Hardware/CANdriver.h"
#include <util/atomic.h>

//
//instance()
//

CANhardware* CANhardware::instance()
{
	static CANhardware theCANhardware;
	return &theCANhardware;
}


//
//setBaudRate(uint8)
//

void CANhardware::setBaudRate(uint16_t baud)
{
	if ((baudRate_!= baud) || !initialized_)
	{
		this->stop();
	}
	else
	{
		return;
	}

	//DDRC |= (1<<PINC5); //THIS IS THE INTENDED LED STATUS PIN, SET AS OUTPUT (1)

	CAN_TX_DDR |= (1<<CAN_TX_PIN); //ENABLE AS AN OUTPUT, THE TX PIN FOR CAN
	CAN_TX_DDR &= ~(1<<CAN_RX_PIN); //ENABLE AS AN INPUT, THE RX PIN FOR CAN

	///////////////////////////	///////////////////////////	///////////////////////////
	unsigned char mob;          // CREATE THE VARIABLE FOR LATER USE TO INDEX WHICH MOB IS BEING REFERENCED
	if (!initialized_)
	{
		Can_reset(); //CANGCON = (1 << SWRES);     // Reset the CAN controller hardware and general registers.
	}
	///////////////////////////	///////////////////////////	///////////////////////////

	///////////////////////////	///////////////////////////	///////////////////////////
	// Initialize the MObs for the AT90CANxxx family. MOb values are not reset initialized. - THE ENTIRE OF THE MOB MUST BE CLEARED... THEY ARE FILLED WITH GARBAGE DATA ON THE FIRST START
	if (initialized_)
	{
		for (mob = 0; mob < MAXIMUM_MOB; mob++)  //STEP THROUGH ALL THE MOB'S
		{
			Can_set_mob(mob); //CANPAGE = (mob << MOBNB0);  // Set the MOb number for each MOb (AINC=0 and INDX=0). - AUTO INCREMENT SET TO 0, AND THE INDEX IS SET TO 0 AUTOMATICALLY AT A NEW CANPAGE CALL
			CANSTMOB = 0x00;            // CLEAR ALL THE STATUS FLAGS FOR EACH OF THE 14 MOBS
		}
	}
	else
	{
		for (mob = 0; mob < MAXIMUM_MOB; mob++)  //STEP THROUGH ALL THE MOB'S
		{
			Can_set_mob(mob); //CANPAGE = (mob << MOBNB0);  // Set the MOb number for each MOb (AINC=0 and INDX=0). - AUTO INCREMENT SET TO 0, AND THE INDEX IS SET TO 0 AUTOMATICALLY AT A NEW CANPAGE CALL
			this->insertData(0,mob,0);
			this->setIdentity(0,mob);
			this->setMask(UINT32_MAX,mob);
			CANCDMOB = ((canVersionBEnabled_&1)<<IDE);	        // SET THE CONFIGURATION OF ALL THE MOBS TO NOTHING
			CANSTMOB = 0x00;            // CLEAR ALL THE STATUS FLAGS FOR EACH OF THE 14 MOBS
		}
	}


#include "Hardware\CANHardwareClockSettings.h"


	if (!initialized_)
	{
		// Enable interrupts for RXOK and TXOK.
		CANGIE = (1 << ENIT) | (1 << ENRX) | (1 << ENTX) | (0<<ENERG);	//TURN ON THE RX FLAG AND ENABLE INTERUPTS WITH ENIT
		CANIE2 = 0x00; //ENABLE NO MOB REGISTER INTERRUPTS FOR NOW
		CANIE1 = 0x00; //ENABLE NO MOB REGISTER INTERRUPTS FOR NOW
		///////////////////////////	///////////////////////////	///////////////////////////

		///////////////////////////	///////////////////////////	///////////////////////////
		// USE THIS SECTION OF THE CODE TO CONFIGURE THE MOB OF THE RECEIVE MULE OF THE SYSTEM.
		Can_set_mob(0);//CANPAGE=0b00000000;; //GET MOB 0 UP TO BAT~~
		///////////////////////////	///////////////////////////	///////////////////////////

		//// == CONFIGURE THE TIMESTAMP PRECALER
		CANTCON = 200; //TIMESTAMPtime = 8*Fcpu*CANTCON.... configure for 1/10ms per bit of lower register timestamp
		//// ==

		//THIS CODE PROVIDES VALID 11-BIT BUS TRAFFIC, TO SWITCH TO 29 BIT, GO TO PAGE 184 OF THE MANUAL FOR THE IDE BIT, ALONG WITH EXPLANATION OF THE TX/RX CONFIG REGISTERS IN THAT CASE
		CANGIT = 0;
		//CANSTMOB = 0;
	}

	if (initialized_)
	{
		this->start();
	}

	initialized_ = true;
}


//
//start()
//

void CANhardware::start()
{
	if (initialized_)
	{
		Can_enable(); //CANGCON |= (1 << ENASTB);    // START THIS BITCH UP~~~~
	}
	else
	{
		this->setBaudRate(baudRate_);
		Can_enable(); //CANGCON |= (1 << ENASTB);    // START THIS BITCH UP~~~~
	}
}


//
//stop()
//

void CANhardware::stop()
{
	Can_disable(); //CANGCON &= ~(1 << ENASTB);    // START THIS BITCH UP~~~~
}


//
//listenOnlyMode()
//

void CANhardware::listenOnlyMode()
{

}


//
//send(canPack*)
//

void CANhardware::send(canPack* message)
{
//  	this->hwSend(message); 
//  	return;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (bufferContent_)
		{
			this->addToBuffer(message);
		}
		else
		{
			bufferContent_ = true;
			this->addToBuffer(message);
			this->sendNextInBuffer();
		}
	}
}

//
//hwSend(canPack*)
//

bool CANhardware::hwSend(canPack* message)
{
	uint8_t canpageValue; 
	
		while ((CANGSTA & (1<<RXBSY)) || (CANGSTA & (1<<TXBSY))) //WAIT UNTIL THERE'S NO CAN ACTIVITY
		{
			addToBuffer(message);
			return false;
		}
	
		if (message->mobSerialNumber<MAXIMUM_MOB)
		{
			Can_set_mob(message->mobSerialNumber); //CANPAGE = (message->mobSerialNumber<<MOBNB0);
			restoreRX_=(CANCDMOB & (1<<CONMOB1));
			restoreRXMOB_ = message->mobSerialNumber; 
			CANCDMOB &= ~(1<<CONMOB1); 

 			this->insertData(message->FULL64BITtxFIELD, message->mobSerialNumber, message->messageDLC);
 			this->setIdentity(message->Identity,message->mobSerialNumber);
			//CANPAGE = (message->mobSerialNumber<<MOBNB0);
		}
		else
		{
			Can_set_mob(SEND_MOB_LOCATION); //CANPAGE = (SEND_MOB_LOCATION<<MOBNB0);	// MAKE SURE THE SEND MULE MOB IS BEING STUFFED, HERE.
			//CANCDMOB &= ~(3<<CONMOB0);
			//CANCDMOB |= (1<<CONMOB1);				//enable RX
			restoreRX_=(CANCDMOB & (1<<CONMOB1));
			restoreRXMOB_ = SEND_MOB_LOCATION;
			CANCDMOB &= ~(3<<CONMOB0);
			CANIE2 |= (1<<SEND_MOB_LOCATION);		//ENABLE MOB INTERRUPT
			//CANIE1 = 0x00;						//ENABLE MOB INTERRUPT
			CANGIE |= (1<<ENTX); 		//ENABLE rx interrupt of this mob
			this->setIdentity(message->Identity,SEND_MOB_LOCATION);
			this->insertData(message->FULL64BITtxFIELD, SEND_MOB_LOCATION, message->messageDLC);
			Can_set_mob(SEND_MOB_LOCATION);//CANPAGE = (SEND_MOB_LOCATION<<MOBNB0);	// MAKE SURE THE SEND MULE MOB IS BEING STUFFED, HERE.
		}
 
		CANCDMOB |= (1<<CONMOB0); //SEND THE DATA
		return true;
}


//
//add (Listener*, canPack*)
//

void CANhardware::add(Listener* listener, canPack* message)
{
	uint8_t i = 0;
	uint8_t cdMOBValue;
	uint64_t tempdelete;

	//message->FULL64BITtxFIELD |= (message->mobSerialNumber<<0); //TODO this doesn't seem to make much sense... why do it?

	if ((message->direction == TX) && !(message->RTRenabled)) //THE MESSAGE DOESN'T NEED A PHYSICAL MOB
	{ //start from the list bottom (not physical mob locations)
		for(i=(MAXIMUM_CAN_MESSAGES-1); i>=0; i--)
		{
			if ((listOfMessages_[i].message == 0) && (i!=SEND_MOB_LOCATION))
			{
				//add message
				listOfMessages_[i].message = message;
				listOfMessages_[i].listener = listener;
				message->mobSerialNumber = i;
				break;
			}
		}
	}
	else
	{//start from the top of the list to add the message (prefer physical mob)
		for(i=0; i<MAXIMUM_CAN_MESSAGES; i++)
		{
			if ((listOfMessages_[i].message == NULL) && (i!=SEND_MOB_LOCATION))
			{
				//add message
				listOfMessages_[i].message = message;
				listOfMessages_[i].listener = listener;
				message->mobSerialNumber = i;
				break;
			}
		}
	}
	//todo this makes NO SENSE
	/*
	message->FULL64BITtxFIELD |= (message->mobSerialNumber<<8);
	tempdelete = CANPAGE;
	message->FULL64BITtxFIELD |= tempdelete<<16;
	tempdelete = CANCDMOB;
	message->FULL64BITtxFIELD |= tempdelete<<24;
	*/
	
	if (message->mobSerialNumber>=MAXIMUM_MOB)
	{
		//Perform hardware assignments for SEND_MOB_LOCAION / overflow messages

		//Create composite mask and identity for SEND_MOB_LOCATION
		this->generateComposites();
		
		Can_set_mob(SEND_MOB_LOCATION);//CANPAGE = (SEND_MOB_LOCATION<<MOBNB0);
		CANCDMOB = 0;
		
		this->setIdentity(overflowMOBIdent_, SEND_MOB_LOCATION);
		this->setMask(overflowMOBMask_, SEND_MOB_LOCATION);

		Can_set_mob(SEND_MOB_LOCATION);//CANPAGE = (SEND_MOB_LOCATION<<MOBNB0);

		CANCDMOB &= ~(1<<RPLV); 				//This MOB can't support instant replies
		CANCDMOB |= (1<<CONMOB1); 				//ENABLE rx of this message (needed for REQUEST)
		
		CANGIE |= (1<<ENIT) | (1<<ENRX) | (1<<ENTX); 		//ENABLE rx interrupt of this mob
		Can_set_dlc(0x0F & message->messageDLC); //CANCDMOB |= 0x0F & message->messageDLC;//PER DATASHEET, values greater than 8 saturate to 8 in the dlc field
	}
	else
	{
		//BRING UP THE SELECTED MOB SLOT
// 		CANPAGE = (identity->mobSerialNumber<<MOBNB0);
// 		CANCDMOB = 0;
		
		this->setIdentity(message->Identity, message->mobSerialNumber);
		this->setMask(UINT32_MAX, message->mobSerialNumber);

		cdMOBValue |= ((message->RTRenabled & 1)<<RPLV);

		cdMOBValue |= (0x0F & message->messageDLC);
		
		cdMOBValue |= ((canVersionBEnabled_&1)<<IDE);
		
		this->insertData(UINT64_MAX, message->mobSerialNumber, message->messageDLC);

		CANPAGE = (message->mobSerialNumber<<MOBNB0);
		if ((message->mobSerialNumber<MAXIMUM_MOB) && ((message->direction==RX) || (message->direction == BOTH)))
		{
			cdMOBValue |= (1<<CONMOB1); 			//ENABLE rx of this message
			CANGIE |= (1<<ENIT) | (1<<ENRX); 		//ENABLE rx interrupt of this mob
		}
		tempdelete =  cdMOBValue;
		message->FULL64BITtxFIELD |= (tempdelete<<32);
		CANCDMOB = cdMOBValue;
		CANIE2 |= (1<<message->mobSerialNumber);//ENABLE MOB INTERRUPT
		tempdelete = CANIE2;
		message->FULL64BITtxFIELD |= (tempdelete<<40);
		tempdelete = CANGIE;
		message->FULL64BITtxFIELD |= (tempdelete<<48);
		//CANIE1 = 0x00;						//ENABLE MOB INTERRUPT
		CANGIE |= (1<<ENIT) | (1<<ENTX); 		//ENABLE rx interrupt of this mob
		tempdelete = CANGIE;
		message->FULL64BITtxFIELD |= (tempdelete<<56);
	}
}


//
//insertData(uint64_t*, uint8_t, uint8_t)
//

void CANhardware::insertData(uint64_t data, uint8_t mob, uint8_t dlc)
{
	uint8_t i = 0;
	if (mob<MAXIMUM_MOB) //CHECK FOR VALID MOB
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			Can_set_mob(mob); //CANPAGE = i;
			Can_set_zero_index();
			//insert the data into the message buffer
			for (i=0; i<dlc; i++)
			{
				Can_set_data_byte(data); //CANMSG = 0xFF & (data);
				data = (data>>8);
			}
			//use i for new purpose
			//i = CANCDMOB;
			//i &= ~(0xF<<DLC0);
			//i |= (dlc<<DLC0);
			Can_set_dlc(dlc); //CANCDMOB = i;
		}
	}
	
}


//
//insertData(uint8_t)
//

uint64_t CANhardware::extractData(uint8_t mob, uint8_t dlc)
{
	uint8_t i, shift;
	uint64_t data, temp;
	shift = 0;
	data = 0;
	if (mob<MAXIMUM_MOB) //CHECK FOR VALID MOB
	{
		Can_set_mob(mob); //CANPAGE = (mob<<MOBNB0);

		//extract the data into the message buffer
		for (i=0; i<dlc; i++)
		{	
			temp = Can_get_data_byte();
			data |= (temp<<shift);
			shift+=8;
		}

		//FILL THE REMAINDER OF THE MESSAGE WITH 0XFF if the DLC<8
		if (dlc!=8)
		{
			for (i=dlc; i<8; i++)
			{
				temp = 0xFF;
				data |= (temp<<shift);
				shift+=8;
			}
		}

		return data;
	}
	else //NOT A VALID MOB
	{
		return 0;
	}
}


//
//setIdeneity(uint32, uint8)
//

void CANhardware::setIdentity(uint32_t identity, uint8_t mob)
{
	uint8_t canpageValue;
	
	if (mob<MAXIMUM_MOB) //CHECK FOR VALID MOB
	{
		//canpageValue = CANPAGE;
		//canpageValue &= ~(0xF<<MOBNB0);
		//canpageValue |= (mob<<MOBNB0);
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//CANPAGE = canpageValue;
			Can_set_mob(mob);

			if (canVersionBEnabled_)
			{
				Can_set_ext_id(identity);
				/*CANIDT4 &= ~(0xFF<<3) | 0X07;	  	//0'S inserted to the leftmost 5 bits
				CANIDT4 |= (identity << 3) & 0xF8; 	//Bits 0-4
				CANIDT3 = 0xFF & (identity >> 5); 	//Bits 5-12
				CANIDT2 = 0xFF & (identity >> 13);	//Bits 13-20
				CANIDT1 = 0xFF & (identity >> 21);  //Bits 21-28
				CANCDMOB |= (1<<IDE);*/
			}
			else
			{
				Can_set_std_id(identity);
				//CANIDT4 &= ~(0xFF<<3) | 0X07;		//0'S inserted to the leftmost 5 bits
				//CANIDT3 = 0x00; 					//unused
				//CANIDT2 = (identity << 5) & 0xE0;	//Bits 0-2
				//CANIDT1 = 0xFF & (identity >> 3);  	//Bits 3-10//unused
				//CANCDMOB &= ~(1<<IDE);
			}
		}
	}
}


//
//setMask(uint32_t, uint8_t)
//

void CANhardware::setMask(uint32_t mask, uint8_t mob)
{
	if (mob<MAXIMUM_MOB) //CHECK FOR VALID MOB
	{
		Can_set_mob(mob); //CANPAGE = (mob<<MOBNB0);

		if (!canVersionBEnabled_)
		{
			Can_set_ext_msk(mask); /*
			CANIDM4 = (0<<RTRMSK) | (1<<IDEMSK);  //require that it be the same length, but accept all rtr
			CANIDM3 = 0x00;
			CANIDM2 = 0xFF & (mask<<5);
			CANIDM1 = 0xFF & (mask>>3);*/
		}
		else
		{
			Can_set_std_msk(mask); /*
			CANIDM4 = (0xFF & (mask<<3)) | (0<<RTRMSK) | (1<<IDEMSK);  //require that it be the same length, but accept all rtr
			CANIDM3 = 0xFF & (mask >> 5);
			CANIDM2 = 0xFF & (mask >> 13);
			CANIDM1 = 0xFF & (mask >> 21);*/
		}
	}
}


//
//update(canPack*)
//

void CANhardware::update(canPack* message)
{
	uint8_t temp; 
	if (message->mobSerialNumber<MAXIMUM_MOB)
	{
		this->insertData(message->FULL64BITtxFIELD, message->mobSerialNumber, message->messageDLC);
		this->setIdentity(message->Identity,message->mobSerialNumber);
		if (message->direction != TX)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				Can_set_mob(message->mobSerialNumber); //CANPAGE = (message->mobSerialNumber<<MOBNB0);
				/*temp = CANCDMOB;
				temp &= ~((1<<CONMOB1) | (1<<CONMOB0));*/
				Can_config_rx();
				/*temp |= ((1 & message->RTRenabled)<<RPLV) | (1<<CONMOB1);//READY FOR RX
				CANCDMOB = temp;*/
				if (message->RTRenabled) {Can_set_rplv();}
			}
		}
	}
}


//
//remove (canPack*)
//

void CANhardware::remove(canPack* identity)
{
	uint8_t i =0;

	for(i=0; i<MAXIMUM_CAN_MESSAGES; i++)
	{
		if (listOfMessages_[i].message->Identity == identity->Identity)
		{
			//REMOVE message from list
			listOfMessages_[i].message = NULL;
			listOfMessages_[i].listener = NULL;

			if (identity->mobSerialNumber >= MAXIMUM_MOB)
			{
				this->generateComposites();

				this->setIdentity(overflowMOBIdent_,SEND_MOB_LOCATION);
				this->setMask(overflowMOBMask_, SEND_MOB_LOCATION);
			}
			else
			{
				CANIE2 &= ~(1<<identity->mobSerialNumber); 				//DISABLE MOB INTERRUPT
				this->setIdentity(0, identity->mobSerialNumber);		//REMOVE THE IDENTITY FROM THE MOB
				this->setMask(UINT32_MAX, identity->mobSerialNumber);	//RESET THE MASK OF THE MOB
		
				Can_set_mob(identity->mobSerialNumber); //CANPAGE = (identity->mobSerialNumber<<MOBNB0);
				CANCDMOB = 0;
			}

			identity->mobSerialNumber = 0XFF;
			return;
		}
	}
}


//
//generateComposites()
//

void CANhardware::generateComposites()
{
	uint8_t i = 0;
	overflowMOBMask_ = UINT32_MAX;
	overflowMOBIdent_ = 0;

	for (i=0; i<MAXIMUM_CAN_MESSAGES; i++)
	{
		if (listOfMessages_[i].message->mobSerialNumber >= MAXIMUM_MOB)
		{
			overflowMOBMask_ &= ~((listOfMessages_[i].message->Identity)^(overflowMOBIdent_));
			overflowMOBIdent_ |= listOfMessages_[i].message->Identity;
		}
	}

}


//
//rxInterruptHandler()
//

void CANhardware::rxInterruptHandler(uint8_t mob, uint8_t status)
{
	uint16_t mobInterrupts; 
	uint8_t i;
	mobInterrupts = (CANSIT1<<8) | (CANSIT2<<0);
	
	for (i=0; i<MAXIMUM_CAN_MESSAGES; i++)
	{														//INTERROGATE EACH INSIDE THE LIST OF MESSAGES
		if (listOfMessages_[i].message != NULL)
		{													//MESSAGE HAS BEEN REGISTERED IN THIS INDEX
			if (listOfMessages_[i].message->mobSerialNumber < MAXIMUM_MOB)
			{												//THE MESSAGE HAS A REAL MOB ASSOCIATED
				if (listOfMessages_[i].message->mobSerialNumber == mob)
				{   										//THE INTERRUPT WAS FOR THIS MESSAGE
							
					Can_set_mob(listOfMessages_[i].message->mobSerialNumber); //CANPAGE = (listOfMessages_[i].message->mobSerialNumber<<MOBNB0);

					if ((status & (1<<RXOK)) && !(status & (1<<DLCW))) //if the interrupt is for RX and isn't remote frame
					{										//THE INTERRUPT WAS FOR A SUCCESSFUL RX
						listOfMessages_[i].message->FULL64BITrxFIELD = this->extractData(listOfMessages_[i].message->mobSerialNumber,listOfMessages_[i].message->messageDLC);

						if (listOfMessages_[i].listener != NULL)
						{
							listOfMessages_[i].listener->listenerEvent();
						}
					}
					else
					{
						//status &= ~((1<<RXOK) | (1<<DLCW));
						//CANSTMOB = status;	//CLEAR THE INTERRUPT OF RXOK
					}
				}
			}
			else
			{
				//investigate virtual mob by interrogating the identies
			}
		}
	}
}


//
//txInterruptHandler()
//
	
void CANhardware::txInterruptHandler()
{
	this->sendNextInBuffer();
}


//
//addToBuffer(canPack*)
//

void CANhardware::addToBuffer(canPack* message)
{
	uint8_t i, targetNode; 
	targetNode = 0xFF; 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
			for (i=0; i<MAXIMUM_CAN_BUFFER_SIZE; i++)
			{
				if (messageSendBuffer_[i] == message)
				{
					return;
				}
				
				if (messageSendBuffer_[i] == 0)
				{
					if(targetNode == 0xFF)
					{
						targetNode = i;
					}
				}
			}
			
			if (targetNode != 0xFF)
			{
				messageSendBuffer_[targetNode] = message;
			}
	}
}


//
//removeFromBuffer(canPack*)
//

void CANhardware::removeFromBuffer() 
{
	for (uint8_t i = 0; i<(MAXIMUM_CAN_BUFFER_SIZE-1); i++)
	{
		messageSendBuffer_[i] = messageSendBuffer_[i+1];
	}
	messageSendBuffer_[MAXIMUM_CAN_BUFFER_SIZE] = 0;
	
	if (messageSendBuffer_[0] == NULL)
	{
		bufferContent_ = false; 
	}
}


//
//pullNextFromBuffer()
//

canPack* CANhardware::pullNextFromBuffer()
{
	return messageSendBuffer_[0];	
}


//
//getNextInBuffer();
//

void CANhardware::sendNextInBuffer()
{	
	canPack* message; 
	message = this->pullNextFromBuffer();
	if (message != 0)
	{
		this->hwSend(message);	 
	}
	this->removeFromBuffer();	
}


//
//errInterruptHandler()
//

void CANhardware::errInterruptHandler()
{

}


//
//interruptHandler()
//
	
void CANhardware::interruptHandler()
{	
	uint8_t status, mob;
	uint16_t mobInterrupts;
	
	mobInterrupts = (CANSIT1<<8) | (CANSIT2<<0);
	
		for (mob=0; mob<MAXIMUM_MOB; mob++)
		{
			if (mobInterrupts & (1<<mob))
			{	//CONVERT INTERRUPT INTO AN MOB NUMBER
				CANPAGE = (mob<<MOBNB0);
				
				status = CANSTMOB;
				
				if (status & (1<<RXOK))
				{
					this->rxInterruptHandler(mob, status);
				}
				
				if (status & (1<<TXOK))
				{	
					this->txInterruptHandler();
					//PORTB ^= (1<<PINB6);
					if (mob == restoreRXMOB_)
					{
						CANPAGE = (mob<<MOBNB0);
						CANCDMOB &= ~(0x3<<CONMOB0);
						CANCDMOB |= ((restoreRX_&1)<<CONMOB1);
						restoreRX_ = false;
						restoreRXMOB_ = 0xFF; 
					}
				}
				CANPAGE = (mob<<MOBNB0);
				CANSTMOB = 0;
			}															
		}
}
