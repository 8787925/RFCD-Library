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


//
// Ports
//
//defines the list of ports, representing 1 (in use) and 0 (not in use)
//

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

//
//Operator Overloading for Ports
//

Ports operator |= (Ports& lhs, Ports& rhs)
{	Ports local;
	local.Port_A = (lhs.Port_A | rhs.Port_A);
	local.Port_B = (lhs.Port_B | rhs.Port_B);
	local.Port_C = (lhs.Port_C | rhs.Port_C);
	local.Port_D = (lhs.Port_D | rhs.Port_D);
	local.Port_E = (lhs.Port_E | rhs.Port_E);
	local.Port_F = (lhs.Port_F | rhs.Port_F);
	local.Port_G = (lhs.Port_G | rhs.Port_G);
	local.Port_H = (lhs.Port_H | rhs.Port_H);
	local.Port_I = (lhs.Port_I | rhs.Port_I);
	return local;
}

Ports operator &= (Ports& lhs, Ports& rhs)
{	Ports local;
	local.Port_A = (lhs.Port_A & rhs.Port_A);
	local.Port_B = (lhs.Port_B & rhs.Port_B);
	local.Port_C = (lhs.Port_C & rhs.Port_C);
	local.Port_D = (lhs.Port_D & rhs.Port_D);
	local.Port_E = (lhs.Port_E & rhs.Port_E);
	local.Port_F = (lhs.Port_F & rhs.Port_F);
	local.Port_G = (lhs.Port_G & rhs.Port_G);
	local.Port_H = (lhs.Port_H & rhs.Port_H);
	local.Port_I = (lhs.Port_I & rhs.Port_I);
	return local;
}

bool operator == (Ports& lhs, Ports& rhs)
{	int local;
	local |= (lhs.Port_A & rhs.Port_A);
	local |= (lhs.Port_B & rhs.Port_B);
	local |= (lhs.Port_C & rhs.Port_C);
	local |= (lhs.Port_D & rhs.Port_D);
	local |= (lhs.Port_E & rhs.Port_E);
	local |= (lhs.Port_F & rhs.Port_F);
	local |= (lhs.Port_G & rhs.Port_G);
	local |= (lhs.Port_H & rhs.Port_H);
	local |= (lhs.Port_I & rhs.Port_I);
	return (local > 0);
}

Ports operator ~ (Ports& lhs)
{	Ports local;
	local.Port_A = ~lhs.Port_A;
	local.Port_B = ~lhs.Port_B;
	local.Port_C = ~lhs.Port_C;
	local.Port_D = ~lhs.Port_D;
	local.Port_E = ~lhs.Port_E;
	local.Port_F = ~lhs.Port_F;
	local.Port_G = ~lhs.Port_G;
	local.Port_H = ~lhs.Port_H;
	local.Port_I = ~lhs.Port_I;
	return local;
}



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
