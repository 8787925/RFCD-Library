
#include <DeviceTracker.h>


//
//Instance()
//

devicePortUse * devicePortUse::instance(){
	static devicePortUse thedevicePortUse;
	return & thedevicePortUse;
}


//
//checkOut(Ports)
//

bool devicePortUse::checkOut(Ports checkThisPort){

	if (checkThisPort.Port_A & staticPortsCheckout_.Port_A){
		return false;
	}
	if (checkThisPort.Port_B & staticPortsCheckout_.Port_B){
		return false;
	}
	if (checkThisPort.Port_C & staticPortsCheckout_.Port_C){
		return false;
	}
	if (checkThisPort.Port_D & staticPortsCheckout_.Port_D){
		return false;
	}
	if (checkThisPort.Port_E & staticPortsCheckout_.Port_E){
		return false;
	}
	if (checkThisPort.Port_F & staticPortsCheckout_.Port_F){
		return false;
	}
	if (checkThisPort.Port_G & staticPortsCheckout_.Port_G){
		return false;
	}
	if (checkThisPort.Port_H & staticPortsCheckout_.Port_H){
		return false;
	}
	if (checkThisPort.Port_I & staticPortsCheckout_.Port_I){
		return false;
	}

	staticPortsCheckout_ |= checkThisPort;
	/*staticPortsCheckout_.Port_B |= checkThisPort.Port_B;
	staticPortsCheckout_.Port_C |= checkThisPort.Port_C;
	staticPortsCheckout_.Port_D |= checkThisPort.Port_D;
	staticPortsCheckout_.Port_E |= checkThisPort.Port_E;
	staticPortsCheckout_.Port_F |= checkThisPort.Port_F;
	staticPortsCheckout_.Port_G |= checkThisPort.Port_G;
	staticPortsCheckout_.Port_H |= checkThisPort.Port_H;
	staticPortsCheckout_.Port_I |= checkThisPort.Port_I;*/

	return true;
}


//
//checkIn(Ports)
//

void devicePortUse::checkIn(Ports checkThisPort){
	staticPortsCheckout_ &= ~(checkThisPort);
	/*staticPortsCheckout_.Port_B &= ~(checkThisPort.Port_B);
	staticPortsCheckout_.Port_C &= ~(checkThisPort.Port_C);
	staticPortsCheckout_.Port_D &= ~(checkThisPort.Port_D);
	staticPortsCheckout_.Port_E &= ~(checkThisPort.Port_E);
	staticPortsCheckout_.Port_F &= ~(checkThisPort.Port_F);
	staticPortsCheckout_.Port_G &= ~(checkThisPort.Port_G);
	staticPortsCheckout_.Port_H &= ~(checkThisPort.Port_H);
	staticPortsCheckout_.Port_I &= ~(checkThisPort.Port_I);*/

	//staticPortsCheckout_ = (staticPortsCheckout_ & (~checkThisPort));//no idea at all if this would work
}


//
//Ports getRegister()
//

Ports devicePortUse::getRegister(){
	return staticPortsCheckout_;
}


//
//constructor()
//

devicePortUse::devicePortUse(){
	//nothing
		staticPortsCheckout_.Port_A = 0;
		staticPortsCheckout_.Port_B = 0;
		staticPortsCheckout_.Port_C = 0;
		staticPortsCheckout_.Port_D = 0;
		staticPortsCheckout_.Port_E = 0;
		staticPortsCheckout_.Port_F = 0;
		staticPortsCheckout_.Port_G = 0;
		staticPortsCheckout_.Port_H = 0;
		staticPortsCheckout_.Port_I = 0;
}


//=============================================

//
//Instance()
//

deviceMobUse * deviceMobUse::instance(){
	static deviceMobUse thedeviceMobUse;
	return & thedeviceMobUse;
}


//
//checkOut(MOBspot)
//

bool deviceMobUse::checkOut(MOBspot mob){

	if ((1<<mob) & StaticMobs_)
	{
		//the device is in use
		return false;
	}

	//the device is free
	StaticMobs_ |= (1<<mob);
	return true;
}


//
//checkIn(MOBspot)
//

void deviceMobUse::checkIn(MOBspot mob){
	StaticMobs_ &= ~(1<<mob);
}


//
//MOBregister getRegister()
//

MOBregister deviceMobUse::getRegister(){
	return StaticMobs_;
}


//
//MOBspot getNext()
//

MOBspot deviceMobUse::getNext(){
	uint8_t i;
	for (i=0;i<MOBspot::extent;i++)
	{
		if(this->checkOut(static_cast<MOBspot>(i)))
		{
			return static_cast<MOBspot>(i);//return the successful checkout MOB
		}
	}
	return MOBspot::extent;
}


//
//constructor()
//

deviceMobUse::deviceMobUse(){
	StaticMobs_ = 1; //mob0 is not to be used as an Rx mob
}

