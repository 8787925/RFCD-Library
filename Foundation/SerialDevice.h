/*
 * SerialDevice.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Jimmy
 */

#ifndef FOUNDATION_SERIALDEVICE_H_
#define FOUNDATION_SERIALDEVICE_H_

//#include "Config.h"


#include "DataRequest.h"
#include "SerialMessageKit.h"
#include "PointerListKit.h"
#include "PointerBuffer.h"
#include "VariableListKit.h"

#ifndef MAXIMUM_SERIAL_RX_MESSAGES
#define MAXIMUM_SERIAL_RX_MESSAGES 10
#endif

#ifndef TERMINATING_CHARACTER
#define TERMINATING_CHARACTER 0x13  //[CR] is considered the end of a sentence
#endif

#ifndef SERIAL_IDENTIFIER_LENGTH
#define SERIAL_IDENTIFIER_LENGTH 5
#endif

template <const uint8_t BUFFERLENGTH, const uint8_t IDENTITY_LENGTH>

class SerialDevice: public FifoPointerBuffer <DataRequest, BUFFERLENGTH>
{
public:
	//
	//constructor
	//

	SerialDevice(): rollingIdentity(0), rxDataBuffer(60)
	{
		clientRxMessageIdentifier_ = 0;
		enabled_ = false;
		transmitting_ = false;
		clientRxMessageIdentifier_ = 0;
		recieving_ = false;
		incomingPayloadCount_ = 0;
		streamIsNew_ = false;
		for (int i = 0; i<SERIAL_IDENTIFIER_LENGTH; i++)
		{
			temporaryIdentity_[i] = 0;
		}
	}


	//
	//startStream(ByteRequest*)
	//

	virtual void startStream(DataRequest* byteRequest)
	{
		this->add(byteRequest);
		this->beginTransmission(); //serial device driver is to include this class and have a real method
	}


	//
	//finishedStream(ByteRequest*)
	//

	virtual void finishedStream(DataRequest* byteRequest)
	{
		this->remove(byteRequest);
	}


	//
	//isBusy()
	//

	virtual bool isBusy()
	{
		return (transmitting_ || recieving_);
	}


	//
	//beginTransimission()
	//

	virtual void beginTransmission()
	{
		return;
	}


	//
	//status()
	//

	virtual bool status()
	{
		return enabled_;
	}


	//
	//enable()
	//

	virtual void enable()
	{
		enabled_ = true;
	}


	//
	//disable()
	//

	virtual void disable()
	{
		enabled_ = false;
	}


	//
	//rxManager(uint8_t)
	//

	void rxManager(uint8_t data)
	{
		if (!recieving_) //if we're not currently recieving, search for valid identities incoming
		{
			rollingIdentity.insertAtBottom(data);

			bool searchDone = true;
			bool firstLoop = true;
			uint8_t itterationPosition = 0;

			for (uint8_t i = 0; i < rxList_.used(); i++)
			{
				//firstLoop = false;

				if(rxList_.itterate(&searchDone)->compare(rollingIdentity.getPointer(), rollingIdentity.size()))
				{
					//this means that the current .itterate return matches our records
					clientRxMessageIdentifier_ = rxList_.get(itterationPosition);
					recieving_ = true;
					incomingPayloadCount_ = 0;
					streamIsNew_ = true;
					break;
				}
				itterationPosition++;
			}

		}
		else
		{

			//a session is already open and we're prepared to exit or continue storing bytes
			if (clientRxMessageIdentifier_ == 0) //safety check for null pointer
			{
				return;
			}

			incomingPayloadCount_++;

			if (clientRxMessageIdentifier_->getPayloadType() == ASCII)
			{
				if (data != clientRxMessageIdentifier_->getTerminator())
				{
					//this is still another byte of an incoming stream. Store the byte and wait for more
					this->rxDataBuffer.onPushByte(data, &streamIsNew_);
				}
				else
				{
					//the message is ended, and is ready to be uploaded to the client data payload
					this->rxDataBuffer.onPushByte(data, &streamIsNew_);
					this->uploadBuffer();
					recieving_ = false;
					clientRxMessageIdentifier_->listenerEvent(); //notify client of finished RX
				}
			}
			else //the message is of fixed-byte type
			{
				if (incomingPayloadCount_ < clientRxMessageIdentifier_->getPayloadSize())
				{
					//this is another byte to be stored and then we wait for more
					this->rxDataBuffer.onPushByte(data, &streamIsNew_);
				}
				else
				{
					//the message is ended, and after this final byte is stored; it's ready to be given the buffer content
					this->rxDataBuffer.onPushByte(data, &streamIsNew_);
					this->uploadBuffer();
					recieving_ = false;
					clientRxMessageIdentifier_->listenerEvent(); //notify client of finished RX
				}
			}
		}
	}


	//
	//onListen()
	//

	virtual void listenerEvent()
	{
		return; //TODO this is to be the RX and TX interrupt handler location
	}


	//
	//addRxMessage(SerialIdentifier<IDENT_LENGTH>)
	//

	void addRxMessage(SerialIdentifier<SERIAL_IDENTIFIER_LENGTH> * identity)
	{
		rxList_.add(identity);
	}


	//
	//ponterList of RX messages - variable direct access to the object, instead of a helper
	//

	PointerList <SerialIdentifier<SERIAL_IDENTIFIER_LENGTH>, BUFFERLENGTH> rxList_;

private:
	//
	//uploadBuffer()
	//

	void uploadBuffer()
	{
		if (clientRxMessageIdentifier_ != 0)
		{
			bool bufferStream = true;
			bool clientStream = true;
			bool firstRun = true;
			
			while (!bufferStream || firstRun)
			{
				firstRun = false;
				clientRxMessageIdentifier_->onPushByte(rxDataBuffer.onPullByte(&bufferStream), &clientStream);
			}
		}
	}

	//
	//variables
	//

	bool transmitting_;
	bool recieving_, streamIsNew_;
	bool enabled_;
	VariableList<SERIAL_IDENTIFIER_LENGTH, uint8_t> rollingIdentity;// = VariableList<SERIAL_IDENTIFIER_LENGTH, uint8_t> (0);
	uint8_t temporaryIdentity_[SERIAL_IDENTIFIER_LENGTH];
	uint8_t incomingPayloadCount_;
	SerialIdentifier<SERIAL_IDENTIFIER_LENGTH> * clientRxMessageIdentifier_;
	DataPayload<60> rxDataBuffer;


};


#endif /* FOUNDATION_SERIALDEVICE_H_ */
