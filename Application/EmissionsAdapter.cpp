
#include "EmissionsAdapter.h"


//
//instance()
//

EmissionsAdapter * EmissionsAdapter::instance()
{
	static EmissionsAdapter theEmissionsAdapter(BOTH);
	return &theEmissionsAdapter;
}


//
//Send_Message()
//

void EmissionsAdapter::Send_Message()
{
	canMessage::instance()->send(&EmissionsAdapter.adapterCANPACK_);
}


//
//waterMotorRequest()
//incommingWaterMotorRequest

ThreeStateRequest EmissionsAdapter::waterMotorRequest()
{ //TODO.... HOW DOES ONE MANAGE NO REQUEST IN A MESSAGE RETURN VS REQUEST FOR 0?
	if ((adapterCANPACK_.FULL64BITrxFIELD[0])>>7) != 1)
	{
		if (0x01 & (adapterCANPACK_.FULL64BITrxFIELD[0])>>6) {return tbTrue;} //If the message content is valid, return the right bit
		else {return tbFalse;}
	}
	else
	{
		return tbPassive; //return no request
	}
	
}


