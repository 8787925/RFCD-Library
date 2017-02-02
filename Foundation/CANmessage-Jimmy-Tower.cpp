#define __AVR_ATmega32M1__
#include <config.h>
#include <Foundation/CANmessage.h>
#include <avr/interrupt.h>
#include <avr/io.h>

//#include <stdio.h>

//
// instance()
//

canMessage* canMessage::instance()
{
	static canMessage theCanMessage(DEFAULTBAUD,DEFAULTTX);
	return &theCanMessage;
}


//
//canMessage()
//constructor

 canMessage::canMessage(uint8_t newBaud, uint16_t newAdddress)
{
	sendAddress = 0;
	deadBusCount = 0;
	canPorts_.Port_C = (1<<PINC2) | (1<<PINC3); //CAN tx/rx pins
	calibratorAddress = 0;
	canInit(baudRate, sendAddress); 
};


//
//char* SetupMOB(mob)
//
	
void canMessage::SetupMOB(canPack *destinationCan)
{
	//MOBspot MailBox = destinationCan->direction;
	MOBspot MailBox = deviceMobUse::instance()->getNext();
	uint32_t watchdog = 0;
	while (CAN_IS_BUSY()) //WAIT UNTIL THERE'S NO CAN ACTIVITY
	{	
		watchdog++;						 //increment the watchdog timer
		if (watchdog> 0xFFFE){return;}  //IF ABOUT 1/4 OF A SECOND PASSES (fcpu = 8Mhz), EXIT
	}
	
	
	//CANPAGE = 0b00010000; //put up for bat the MOB we're interested in
	CANPAGE = (MailBox<<4);
	
	//// == SET THE ADDRESS FOR RX
#if (CAN_ID_LENGTH == 29)
	CANIDT1 = ((0x07FF & destinationCan->Identity) >> 3); //SET THE ADDRESS OF THE DEVICE TO THE PASSED VARIABLE IN THE SUB-HEADER
	CANIDT2 = ((0X07FF & destinationCan->Identity) << 5); //CAN 2B NEEDS TO HAVE A DIFFERENT MASK HERE
	//// ==
#else
	
#endif
	//// == MASK TO FORCE A PERFECT COMPARISON
	CANIDM1 = 0xFF;				//SET EXCLUSIVE ADDRESS RECEPTION
	CANIDM2 = (0xFF & 0xE0);	//SET EXCLUSIVE ADDRESS RECEPTION (1 = MUST MATCH SAME FIELD IN IDTn) if 11-bits, must write 0's to the last 5 bits
	CANIDM3 = 0x00; 
	CANIDM4 = (0X00 & 0x07);	//last 3 bits are not address pg186 datasheet
	//// ==
	
	//// == SET UP THE MOB'S RX/TX AND DLC
	CANCDMOB = (2<<CONMOB0) | (0<<RPLV) | (0<<IDE) | (0x0F & destinationCan->messageDLC);
	//// ==
	
	//// == ENABLE THE MAILBOX
	//CANEN2 |= (1<<openMOB);		   //ENABLE THIS MOB FOR USE   THIS DOESN'T DO ANYTHING, IT'S A READ ONLY REGISTER
	////
	
	//// == ENABLE INTERUPTS ON THE MAILBOX
	CANIE2 |= (1<<openMOB);
	////
	
	//// ASSIGN THE CHECKED OUT MOB TO THE DESIRED CAN PACK
	canMessage::mob_[uint8_t(MailBox)]=destinationCan;
	////


 		//case mob2: *canMessage::mob2_=destinationCan;
//  		case mob3: *canMessage::mob3_=destinationCan;
//  		case mob4: *canMessage::mob4_=destinationCan;
//  		case mob5: *canMessage::mob5_=destinationCan;
	//canMessage::openMOB++;
	return;
};
	

//
//send(canPack&)
//

void canMessage::send(canPack * messageBytes)
{	static uint8_t ACKERROR;
	uint8_t i = 0;
	uint32_t watchdog = 0;
	//PORTB=0xff;
	if ((deadBusCount != 0) && (deadBusCount!=100)) {return;}
		
	while ((CANGSTA & (1<<RXBSY)) || (CANGSTA & (1<<TXBSY)) && (watchdog<0xfff)) //WAIT UNTIL THERE'S NO CAN ACTIVITY
	{
		watchdog++;						 //increment the watchdog timer
		if (watchdog> 0xFFFE){deadBusCount++; return;}  //IF ABOUT 1/4 OF A SECOND PASSES (fcpu = 8Mhz), EXIT
	}
	
	CANPAGE=0b00000000; // MAKE SURE THE SEND MULE MOB IS BEING STUFFED, HERE.
	
	//if (CANSTMOB & (1<<AERR)) { return;}//IF THERE'S BEEN A TX ERROR, EXIT AND STOP CARING ABOUT THE BUS
	//CONSUME THE PASSED BYTE ARRAY
	for (i=0; i<messageBytes->messageDLC; i++)
	{
		CANMSG = messageBytes->FULL64BITtxFIELD[i];
	}
	//FILL THE REMAINDER OF THE MESSAGE WITH 0XFF
	if (messageBytes->messageDLC!=8)
	{
		for (i=messageBytes->messageDLC; i<8; i++)
		{
			CANMSG = 0xFF;
		}
	}
	//THIS SUB ASSUMES YOU'VE ALREADY BEEN STUFFING THE SEND-MULE WITH UP-TO-DATE DATA AND WANT TO SEND THE MESSAGE AS IT IS

	uint8_t Can_tx_dlc; //CREATE THE  DATA LENGTH VARIABLE

	//~~~~~~~
	//Can_tx_dlc = 8; //DEFINE ALL THE SENT DATA AS 8 BYTES FOR THIS CODE
	//~~~~~~~

	///////////////////////////	///////////////////////////	///////////////////////////
	//GET THE CORRECT MOB ON THE SLATE TO STUFF IT WITH DATA
	CANPAGE = 0b00000000; //FOR THIS DEVICE, WE ARE GOING TO BE USING MOB0 AS OUR DATA SENDING MULE; THIS ALSO ENSURES THAT THE BYTE IS 0 WITHIN THE MOB
	CANIDT1 = (messageBytes->Identity >> 3); //SET THE ADDRESS OF THE DEVICE TO THE PASSED VARIABLE IN THE SUB-HEADER
	CANIDT2 = (messageBytes->Identity << 5);
	CANIDT3 = 0x00;// NOTHING IN HERE NEEDS TO BE SET IF WE ARE OPERATING ON AN 11 BIT BUS
	CANIDT4 = 0x00;// NOTHING IN HERE NEEDS TO BE SET FOR TRANSMITTING A MESSAGE

	// TRIGGER THE SEND COMMAND OF THE CAN TX
	messageBytes->messageDLC = (0x0F & messageBytes->messageDLC); // sanitize the DLC field
	CANCDMOB = (1<<CONMOB0) | (0<<IDE) | messageBytes->messageDLC; //SEND THE DATA 
	i=0;
	
	//while (!(CANSTMOB & (1<<TXOK))){	} //WAIT PAITIENTLY FOR THE TRANSMISSION TO COMPLETE, FLAGGING THE G PORT FOR A STATUS LED

	//CANSTMOB=0; ////INSTRUCTION MANUAL SAYS THAT YOU HAVE TO CLEAR THE STATUS REGISTER AT THE END OF A TRANSMISSION, AND RECOMMENDS THIS METHOD
	//CANGIT=CANGIT; //CLEAR THE INTERRUPTS
	
	//CANCDMOB=0X00; //NOT SURE WHY I PUT THIS IN HERE, DELETE AT YOUR OWN RISK.
	return;


	//GUESS THAT'S THE END OF THE TRANSMISSION METHOD~~~
}


//
//ReceiveCan(mob, canPack)
//

void canMessage::ReceiveCan(MOBspot whichMOB, canPack *whichMessage)
{	
	CANPAGE = (1 << MOBNB0); //Select the offending Mob TODO MOB IS FIXED
	
	uint8_t eightcount = 0;
	
	if (CANSTMOB & (1<<RXOK)) //MAKE SURE THERE'S DATA TO BE CONSUMED
	{
	for (eightcount = 0; eightcount<8; eightcount++){whichMessage->FULL64BITrxFIELD[eightcount] = CANMSG;} //CONSUME BYTES 0 THROUGH 7, AUTO INCREMENT ENABLED
	}
	
	whichMessage->timeStampH = CANSTMH; // 25.6ms per bit, CONFIGURED IN INIT MEMBER
	whichMessage->timeStampL = CANSTMH; // 0.1ms per bit
	
	CANSTMOB = 0;
	CANCDMOB = (2<<CONMOB0); //THIS IS A RISKY MOVE, BECAUSE IT DOESN'T LET SOFTWARE ACCOUNT FOR THE "NOT RX INTERUPT" CASE
	
}


//
//PostMaster()
//

void canMessage::PostMaster()
{	//this code has to be executed as several IF statements incase multiple interrupts are present
	//mob0 is not allowed to be used as a rx mob
	uint8_t i;

	for (i=0; i<NUMBER_OF_MOBs; i++)
	{
		if (CANSIT2 & (1<<i)){ReceiveCan(static_cast<MOBspot>(i), canMessage::mob_[i]);} //mob1 has an interrupt
	}
	/*
	if (CANSIT2 & (1<<SIT1)){ReceiveCan(mob1, canMessage::mob1_);} //mob1 has an interrupt
  	if (CANSIT2 & (1<<SIT2)){ReceiveCan(mob2, canMessage::mob2_);} //mob2 has an interrupt
  	if (CANSIT2 & (1<<SIT3)){ReceiveCan(mob3, canMessage::mob3_);} //mob3 has an interrupt
  	if (CANSIT2 & (1<<SIT4)){ReceiveCan(mob4, canMessage::mob4_);} //mob4 has an interrupt
  	if (CANSIT2 & (1<<SIT5)){ReceiveCan(mob5, canMessage::mob5_);} //mob5 has an interrupt
  	*/
}


//
//canInit(uint8_t baud, TXorRX txORrx, uint16_t Address);
//

void canMessage::canInit(uint8_t newbaud, uint16_t newAddress)
{
		baudRate = 100;		//update class variable
		if(!devicePortUse::instance()->checkOut(canPorts_))
		{
			return;
		} //if the pins for this device are in use, exit
		DDRC |= (1<<PINC5); //THIS IS THE INTENDED LED STATUS PIN, SET AS OUTPUT (1)
		TXCAN_DDR |= (1<<TXCAN); //ENABLE AS AN OUTPUT, THE TX PIN FOR CAN
		RXCAN_DDR &= ~(1<<RXCAN); //ENABLE AS AN INPUT, THE RX PIN FOR CAN
		///////////////////////////	///////////////////////////	///////////////////////////
		unsigned char mob;          // CREATE THE VARIABLE FOR LATER USE TO INDEX WHICH MOB IS BEING REFERENCED
		CANGCON = (1 << SWRES);     // Reset the CAN controller hardware and general registers.
		///////////////////////////	///////////////////////////	///////////////////////////
		
		///////////////////////////	///////////////////////////	///////////////////////////
		// Initialize the MObs for the AT90CANxxx family. MOb values are not reset initialized. - THE ENTIRE OF THE MOB MUST BE CLEARED... THEY ARE FILLED WITH GARBAGE DATA ON THE FIRST START
		for (mob = 0; mob < 15; mob++)  //STEP THROUGH ALL THE MOB'S
		{
			CANPAGE = (mob << MOBNB0);  // Set the MOb number for each MOb (AINC=0 and INDX=0). - AUTO INCREMENT SET TO 0, AND THE INDEX IS SET TO 0 AUTOMATICALLY AT A NEW CANPAGE CALL
			CANCDMOB = 0x00;	        // SET THE CONFIGURATION OF ALL THE MOBS TO NOTHING
			CANSTMOB = 0x00;            // CLEAR ALL THE STATUS FLAGS FOR EACH OF THE 14 MOBS
		}
		
		//#if (F_CPU==4000000)	//speed-specific baud rate schedule
		if (baudRate == 100)
		{
		///////////////////////////	///////////////////////////	///////////////////////////
		//  CAN baud of XXX k with a 4 MHz AVR clock - STEAL THIS SECTION FROM THE MANUAL, PAGE 188
		CANBT1 = 0x08;              // Timing - Baud Rate Prescaler. See the data sheet errata if CANBT1=0.
		CANBT2 = 0x04;              // Timing - Re-Synchronization Jump Width and Propagation.
		CANBT3 = 0x13;              // Timing - Phase Segment 2, Phase Segment 1 and Sample Point.
		///////////////////////////	///////////////////////////	///////////////////////////
		}
		//#else #error
		//#endif
		
		// Enable interrupts for RXOK and TXOK.
		CANGIE = (1 << ENIT) | (1 << ENRX) | (0 << ENTX) | (1<<ENERG);	//TURN ON THE RX FLAG AND ENABLE INTERUPTS WITH ENIT
		CANIE2 = 0x00; //ENABLE NO MOB REGISTER INTERRUPTS FOR NOW
		CANIE1 = 0x00; //ENABLE NO MOB REGISTER INTERRUPTS FOR NOW
		///////////////////////////	///////////////////////////	///////////////////////////

		///////////////////////////	///////////////////////////	///////////////////////////
		// USE THIS SECTION OF THE CODE TO CONFIGURE THE MOB OF THE RECEIVE MULE OF THE SYSTEM.
		CANPAGE=0b00000000;; //GET MOB 0 UP TO BAT~~
		///////////////////////////	///////////////////////////	///////////////////////////
		
		//// == CONFIGURE THE TIMESTAMP PRECALER
		CANTCON = 200; //TIMESTAMPtime = 8*Fcpu*CANTCON.... configure for 1/10ms per bit of lower register timestamp
		//// ==
		
		//THIS CODE PROVIDES VALID 11-BIT BUS TRAFFIC, TO SWITCH TO 29 BIT, GO TO PAGE 184 OF THE MANUAL FOR THE IDE BIT, ALONG WITH EXPLANATION OF THE TX/RX CONFIG REGISTERS IN THAT CASE
		///CANGCON &= (listenmode<<LISTEN)
		CANGCON |= (1 << ENASTB);    // START THIS BITCH UP~~~~
		CANGIT = 0;
		CANSTMOB = 0;
					// THE OPEN MOB MAILBOXES STARTS AT MOB1 FOR 
}

uint8_t canMessage::openMOB = 1; //THE FIRST AVAILABLE RX MAILBOX FOR CONFIGURATION
