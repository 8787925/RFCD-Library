
#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\FirstDerivativeAdapter.h>


//
//instance()
//

FirstDerivativeMessage* FirstDerivativeMessage::instance()
{ 
	static FirstDerivativeMessage theFirstDerivativeMessage;
	return &theFirstDerivativeMessage;
}


//
//Satellites()
//

uint8_t FirstDerivativeMessage::Satellites()
{
	return satellites_;
}


//
//Send()
//

void FirstDerivativeMessage::Send_Message()
{//	adapterCANPACK_.FULL64BITtxFIELD[0]=(adapterCANPACK_.Identity<<8);
// 	adapterCANPACK_.FULL64BITtxFIELD[1]=adapterCANPACK_.Identity;
// 	adapterCANPACK_.FULL64BITtxFIELD[3]=adapterCANPACK_.messageDLC;
	canMessage::instance()->send(&adapterCANPACK_);
}


//
//Satellites(uint8)
//

void FirstDerivativeMessage::Satellites(uint8_t setSatellites)
{
	satellites_ = setSatellites; 
	adapterCANPACK_.FULL64BITtxFIELD[6] = setSatellites; 
}


//
//VDOP()
//

uint8_t FirstDerivativeMessage::VDOP()
{
	return vdop_; 
}


//
//VDOP(uint8)
//

void FirstDerivativeMessage::VDOP(uint8_t setVDOP)
{
	vdop_ = setVDOP;
	adapterCANPACK_.FULL64BITtxFIELD[5] = setVDOP;
}


//
//Heading()
//

uint16_t FirstDerivativeMessage::Heading()
{
	return heading_;
}


//
//Heading(uint16)
//

void FirstDerivativeMessage::Heading(uint16_t setHeading)
{
	heading_ = setHeading; 
	adapterCANPACK_.FULL64BITtxFIELD[2] = setHeading>>8;
	adapterCANPACK_.FULL64BITtxFIELD[3] = setHeading; 
}


//
//Velocity()
//

uint16_t FirstDerivativeMessage::Velocity()
{
	return velocity_;
}


//
//Velocity(uint16)
//

void FirstDerivativeMessage::Velocity(uint16_t setVelocity)
{
	velocity_=setVelocity; 
	adapterCANPACK_.FULL64BITtxFIELD[0] = setVelocity>>8;
	adapterCANPACK_.FULL64BITtxFIELD[1] = setVelocity; 
}


//
//HDOP()
//

uint8_t FirstDerivativeMessage::HDOP()
{
	return hdop_; 
}


//
//HDOP(uint8)
//

void FirstDerivativeMessage::HDOP(uint8_t setHDOP)
{
	hdop_ = setHDOP; 
	adapterCANPACK_.FULL64BITtxFIELD[4] = hdop_; 
}


//
//constructor()
//

 FirstDerivativeMessage::FirstDerivativeMessage()
{	
	adapterCANPACK_.messageDLC = adapterDLC_; //adapterDLC_;
	adapterCANPACK_.Identity = uint16_t((adapterSA_<<8) | (adapterPGN_));
	//adapterCANPACK_.FULL64BITrxFIELD = 0xFF[8];
	//adapterCANPACK_.FULL64BITtxFIELD = 0XFFFFFFFFFFFFFFFF;
}