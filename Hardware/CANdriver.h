/*
 * CANdriver.h
 *
 *  Created on: Oct 7, 2016
 *      Author: Jimmy
 */

#ifndef HARDWARE_CANDRIVER_H_
#define HARDWARE_CANDRIVER_H_

//
//Includes
//

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\MowerProject\config.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Foundation\Listener.h"
#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\CANTypes.h"

//
//Definition guarding
//

#ifndef MAXIMUM_MOB
#define MAXIMUM_MOB 6
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 0xFFFFFFFFL
#endif

#ifndef UINT64_MAX
#define UINT64_MAX 0xFFFFFFFFFFFFFFFFLL
#endif

#ifndef MAXIMUM_CAN_MESSAGES
#define MAXIMUM_CAN_MESSAGES 6
#endif

#ifndef F_CPU
#define F_CPU 4000000ULL
#endif

#ifndef DEFAULT_CAN_BAUD
#define DEFAULT_CAN_BAUD 100
#endif

#ifndef SEND_MOB_LOCATION
#define SEND_MOB_LOCATION (MAXIMUM_MOB - 1)
#endif

#ifndef MAXIMUM_CAN_BUFFER_SIZE
#define MAXIMUM_CAN_BUFFER_SIZE MAXIMUM_CAN_MESSAGES
#endif

//
//locally used types only
//

struct mobCallBack
{
	Listener* listener;
	canPack* message;
};


//
//CANhardware class
//
//This class is to be aware of hardware features and parameters; and is to
//restrict that knowlege to itself.
//Messages, are to be handed to the class and registered for send
//Messages are to be registered as 'on received'

class CANhardware
{public:

	//
	//instance()
	//

	static CANhardware* instance();


	//
	//setBaudRate(uint8)
	//

	void setBaudRate(uint8_t baud);


	//
	//start()
	//

	void start();


	//
	//stop()
	//

	void stop();


	//
	//listenOnlyMode()
	//

	void listenOnlyMode();

	
	//
	//interruptHandler()
	//
	
	void interruptHandler(); 


	//
	//send(Message*)
	//

	void send(canPack* message);


	//
	//sendRTR(canpack*)
	//

	void sendRTR(canPack* message);


	//
	//add (Listener*, canPack*)
	//

	void add(Listener* listener, canPack* identity);


	//
	//update(canPack*)
	//

	void update(canPack* message);


	//
	//remove (canPack*)
	//

	void remove(canPack* identity);

private:
	//
	//constructor
	//

	CANhardware()
	{
		initialized_=false;
		baudRate_ = DEFAULT_CAN_BAUD;
		canVersionBEnabled_ = true;
		uint8_t i=0;
		for (i=0; i<MAXIMUM_CAN_MESSAGES; i++)
		{
			listOfMessages_[i].message = NULL;
			listOfMessages_[i].listener = NULL;
		}
		for (i=0; i<MAXIMUM_CAN_BUFFER_SIZE; i++)
		{
			messageSendBuffer_[i] = NULL;
		}
		overflowMOBIdent_ = 0;
		overflowMOBMask_ = UINT32_MAX;
		bufferContent_=false;
		sendInProgress_ =false;
		restoreRX_ = false; 
		restoreRXMOB_ = 0xFF; 
	};
	
	
// 	//
// 	//send()
// 	//
// 	//sends the next message in the buffer to hwSend(canPack*) function
// 	//
// 	
// 	void send();


	//
	//restoreRXflags()
	//
	
	void restoreRXflags();  


	//
	//hwSend(Message*)
	//

	bool hwSend(canPack* message);

// 
// 	//
// 	//bufferManager(canpack*)
// 	//
// 	
// 	canPack* bufferManager(canPack* message);


	//
	//rxInterruptHandler()
	//

	void rxInterruptHandler(uint8_t mob, uint8_t status);
	
	
	//
	//txInterruptHandler()
	//
	
	void txInterruptHandler();


	//
	//errInterruptHandler()
	//

	void errInterruptHandler();


	//
	//setMaskAndIdent(uint32, uint32, uint8)
	//

	void setIdentity(uint32_t identity, uint8_t mob);


	//
	//setMask(uint32_t, uint8_t)
	//

	void setMask(uint32_t mask, uint8_t mob);


	//
	//insertData(uint64_t*, uint8_t, uint8_t)
	//

	void insertData(uint64_t data, uint8_t mob, uint8_t dlc);


	//
	//insertData(uint8_t)
	//

	uint64_t extractData(uint8_t mob, uint8_t dlc);


	//
	//generateComposites()
	//

	void generateComposites();


	//
	//addToBuffer(canPack*)
	//

	void addToBuffer(canPack* message);
	
	
	//
	//removeFromBuffer(canPack*)
	//

	void removeFromBuffer();
	
	
	//
	//pullNextFromBuffer()
	//
	
	canPack* pullNextFromBuffer();


	//
	//sendNextInBuffer();
	//

	void sendNextInBuffer();


	//
	//variables
	//

	bool initialized_;
	uint8_t baudRate_;
	bool canVersionBEnabled_;
	mobCallBack listOfMessages_[MAXIMUM_CAN_MESSAGES];
	canPack* messageSendBuffer_[MAXIMUM_CAN_BUFFER_SIZE];
	uint32_t overflowMOBIdent_;
	uint32_t overflowMOBMask_;
	bool bufferContent_;
	bool sendInProgress_;
	bool restoreRX_;
	uint8_t restoreRXMOB_; 

};


#endif /* HARDWARE_CANDRIVER_H_ */
