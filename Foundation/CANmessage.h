#ifndef CANMESSAGE
#define CANMESSAGE

#include <config.h>
#include <DeviceTracker.h>
#include <avr/io.h>

#define DEFAULTTX  0
#define DEFAULTBAUD 100
#define CAN_IS_BUSY() ((CANGSTA & (1<<RXBSY)) || (CANGSTA & (1<<TXBSY)))

enum TXorRX{NEITHER = 0,
			TX = 1,
		    RX = 2,
			BOTH = 3};
	
enum MOBspot{	mob0=0,
				mob1=1,
				mob2=2,
				mob3=3,
				mob4=4,
				mob5=5,
				extent};

struct j1939pgn{
	uint8_t Priority;
	uint8_t SourceAddress;
	uint32_t PGN;};

//
//canPack
//contains the full message both in rx and tx for a given object

struct canPack
	{
		uint8_t FULL64BITtxFIELD [8]; //Right justified for any given DLC packed with 0xF's
		uint8_t FULL64BITrxFIELD [8]; //Right justified for any given DLC packed with 0xF's
		uint8_t messageDLC; 
		uint16_t Identity;
		uint16_t rxIdentity; 
		uint8_t timeStampL;
		uint8_t timeStampH;
		TXorRX direction;
	};	
	
	
class canMessage{
	public:
	//
	// instance(uint Baud, uint16 defaultTx)
	//
	
	static canMessage * instance();

	
	//
	//char* SetupMOB(mob)
	//
	
	void SetupMOB(canPack *destinationCan);
	

	//
	// void Identifier (uint16)
	// Consumes the 16 bit identifier and sets it for the message
	//
	
	void defaultIdentifier(uint16_t cana_BitIdent);
	
	
	//
	// uint16 Identifier ()
	// returns the CAN identifier
		
	uint16_t defaultIdentifier();
	
	
	//
	//send(canPack&)
	//send, the message handed
	
	void send(canPack * messageBytes);
	
	
	//
	//PostMaster()
	//the call for the CAN Rx interrupt
	
	void PostMaster(); 
	
	
	//
	//variables
	//

	uint8_t baudRate = CANBAUDRATE;
	canPack *mob_[NUMBER_OF_MOBs];
	 //canPack *mob1_;
	 //canPack *mob2_;
	 //canPack *mob3_;
	 //canPack *mob4_;
	 //canPack *mob5_;
	 //static uint8_t openMOB;
	private: 

	//
	//ReceiveCan(mob, canPack)
	//
	
	void ReceiveCan(MOBspot whichMOB, canPack *whichMessage);
	
	
	//
	// canMessage(uint Baud, uint18 defaultTx, uint16 calAddress)
	//
	
	 canMessage(uint8_t newBaud, uint16_t newAddress);
	
	
	//
	//canInit(uint8 baud, TXorRX, uint16 )
	//Initialize the can bus
	
	void canInit(uint8_t baud, uint16_t Address);
	
	
	//
	//Private Variables
	//
	
	uint16_t sendAddress;
	uint8_t deadBusCount;
	Ports canPorts_;
	
	uint16_t calibratorAddress;
};
#endif
