// SerialManagerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "C:\Users\mattb\Documents\LocalGit\RFCD-Library\Application\TestAdapter.h"
#include "Foundation\SerialDevice.h"


int main()
{ 
	//
	// message parameters
	//

	txOrRx direction = RXonly;
	const int messageLength = 10;
	const int messageIdentityLength = 5;
	uint8_t terminatorCharacter = 42;
	

	bool success = true; 

	uint8_t n[5];
	cin >> n;
	cout << n << endl;
	
	uint8_t identity[messageIdentityLength]; //the message identity characters used for 
	uint8_t flIdentity[messageIdentityLength];

	for (int i = 0; i < messageIdentityLength; i++)
	{
		flIdentity[i] = char('b');
	};

	for (int i = 0; i < messageIdentityLength; i++)
	{
		identity[i] = char('a');
	};



	SerialMessage<messageLength, messageIdentityLength> theMessage(direction, identity, ASCII, terminatorCharacter);
	SerialMessage<messageLength, messageIdentityLength> theflMessage(direction, flIdentity, BINARY, messageLength);

	bool newStream = true; 

	uint8_t compareValue[messageLength]; 

	for (int x = 0; x < theMessage.getMessageLength(); x++)
	{
		compareValue[x] = rand();
		theMessage.onPushByte(compareValue[x], &newStream);
	}

	cout << "MESSAGE HAS BEEN POPULATED WITH DATA" << endl;

	uint8_t * ident = theMessage.getIdentifier();

	for (int i = 0; i < theMessage.getIdLength(); i++)
	{
		if (ident[i] != identity[i])
		{
			cout << "FAIL: MESSAGE IDENTITY DOES NOT MATCH STORED VALUE" << endl;
			success = false;
		}
	}

	bool pullGood = true;
	bool firstRun = true;
	int bytecount = 0;

	while (!pullGood || firstRun)
	{
		firstRun = false;
		if (theMessage.onPullByte(&pullGood) != compareValue[bytecount])
		{
			cout << "FAIL: MESSAGE CONTENT DOES NOT MATCH STORED VALUES" << endl;
			success = false;
		}
		bytecount++;
	}

	if (success)
	{
		cout << "SUCCESS: THE MESSAGE METHODS ACCEPT AND RETRIEVES DATA IDENTICAL TO STORED VALUES" << endl;
	}
	system("pause");

	const uint8_t testStreamSize = 80;
	const uint8_t staticIntroSize = 8;
	const uint8_t staticOutroSize = testStreamSize - staticIntroSize - messageLength;
	uint8_t testStream[testStreamSize], fltestStream[testStreamSize];
	uint8_t testStreamPayload[messageLength], fltestStreamPayload[messageLength]; 

	SerialDevice<4, messageIdentityLength> theSerialDevice;

	theSerialDevice.addRxMessage(&theMessage); //add the RX message for testing
	theSerialDevice.addRxMessage(&theflMessage); //add the RX (fixed length) message for testing

	for (int i = 0; i < staticIntroSize; i++) //insert the static in the start of the test stream
	{
		testStream[i] = rand();
		fltestStream[i] = testStream[i];
	}

	for (int i = staticIntroSize; i < (staticIntroSize + messageIdentityLength); i++) //insert the identity of the message
	{
		testStream[i] = identity[i - staticIntroSize];
		fltestStream[i] = flIdentity[i - staticIntroSize];
	}

	for (int i = messageIdentityLength + staticIntroSize; i < staticIntroSize+messageIdentityLength+ messageLength; i++) //insert the payload of the message
	{
		if ((i - (staticIntroSize + messageIdentityLength)) == messageLength - 1)
		{
			testStreamPayload[i - (staticIntroSize + messageIdentityLength)] = terminatorCharacter;
			testStream[i] = testStreamPayload[i - (staticIntroSize + messageIdentityLength)];
			break;
		}
		testStreamPayload[i - (staticIntroSize + messageIdentityLength)] = rand();
		fltestStreamPayload[i - (staticIntroSize + messageIdentityLength)] = rand();

		testStream[i] = testStreamPayload[i - (staticIntroSize + messageIdentityLength)];
		fltestStream[i] = fltestStreamPayload[i - (staticIntroSize + messageIdentityLength)];
	}

	for (int i = (staticIntroSize + messageIdentityLength + messageLength); i < testStreamSize; i++) //insert the static following
	{
		testStream[i] = rand();
		fltestStream[i] = testStream[i];
	}

	for (int i = 0; i < testStreamSize; i++)
	{
		theSerialDevice.rxManager(testStream[i]);
	}

	for (int i = 0; i < testStreamSize; i++)
	{
		theSerialDevice.rxManager(fltestStream[i]);
	}

	newStream = true; 
	
	for (int i = 0; i < messageLength; i++)
	{
		if (theMessage.onPullByte(&newStream) != testStreamPayload[i])
		{
			cout << "FAIL: the stored reference in ascii does not match the message content, when administered through the serial manager" << endl;
		}
		else
		{
			//cout << "good" << endl;
		}
	}

	for (int i = 0; i < messageLength; i++)
	{
		if (theflMessage.onPullByte(&newStream) != fltestStreamPayload[i])
		{
			cout << "FAIL: the stored reference in fixed length does not match the message content, when administered through the serial manager" << endl;
		}
		else
		{
			//cout << "good" << endl;
		}
	}

	system("pause");

	//theMessage.compare()

    return 0;
}

