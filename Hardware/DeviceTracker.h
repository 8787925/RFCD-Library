/*
 * DeviceTracker.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_DEVICETRACKER_H_
#define HARDWARE_DEVICETRACKER_H_

#include <avr/io.h>
#include <CANmessage.h>

struct Ports{
	uint8_t Port_A;
	uint8_t Port_B;
	uint8_t Port_C;
	uint8_t Port_D;
	uint8_t Port_E;
	uint8_t Port_F;
	uint8_t Port_G;
	uint8_t Port_H;
	uint8_t Port_I;
};

typedef uint32_t MOBregister;

class deviceMobUse{
public:
	//
	//instance()
	//

	static deviceMobUse * instance();


	//
	//checkOut(mobSpot)
	//

	bool checkOut(MOBspot mob);


	//
	//checkIn(MOBspot)
	//

	void checkIn(MOBspot mob);


	//
	//MOBregister getRegister()
	//
	//returns a bit-array of the used mob's

	MOBregister getRegister();


	//
	//MOBspot getNext()
	//

	MOBspot getNext();

private:
	deviceMobUse();

	MOBregister StaticMobs_;
};


class devicePortUse{
	public:
	//
	//instance()
	//

	static devicePortUse * instance();


	//
	//checkOut(Ports)
	//
	//check if a port is available for device use and if it is, take it

	bool checkOut(Ports checkThisPort);


	//
	//checkIn(Ports)
	//
	//returns the port/pin to be freely modified

	void checkIn(Ports checkThisPort);


	//
	//Ports getRegister()
	//
	//returns the register of used port/pins

	Ports getRegister();
	
	private:
	
	devicePortUse();

	Ports staticPortsCheckout_;
};
#endif /* HARDWARE_DEVICETRACKER_H_ */
