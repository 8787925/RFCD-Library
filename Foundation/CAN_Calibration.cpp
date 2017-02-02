
#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\CAN_Calibration.h>


//
//instance()
//

CAN_Calibration* CAN_Calibration::instance(TXorRX setDireciton)
{
	static CAN_Calibration theCan_Calibration(setDireciton);
	return &theCan_Calibration;
}


//
//Send()
//

void CAN_Calibration::Send_Message()
{
	canMessage::instance()->send(&adapterCANPACK_);
}

//
//Parameter()
//gets the velocity currently set
	
uint16_t CAN_Calibration::Parameter()
{	
	return (adapterCANPACK_.FULL64BITrxFIELD[0]<<8) | (adapterCANPACK_.FULL64BITrxFIELD[1]);
	
}
	
	
//
//Parameter(uint16)
//
	
void CAN_Calibration::Parameter(uint16_t setParameter)
{
	adapterCANPACK_.FULL64BITtxFIELD[0]=(setParameter>>8);
	adapterCANPACK_.FULL64BITtxFIELD[1]=(setParameter);
}
	
	
//
//field1()
//gets the first 16 bit field
	
uint16_t CAN_Calibration::field1()
{
	return ((adapterCANPACK_.FULL64BITrxFIELD[2]<<8) | (adapterCANPACK_.FULL64BITrxFIELD[3]));
}
	
	
//
//field1(uint16)
//sets the first 16-bit field
	
void CAN_Calibration::field1(uint16_t setField1)
{
	adapterCANPACK_.FULL64BITtxFIELD[2]=(setField1>>8);
	adapterCANPACK_.FULL64BITtxFIELD[3]=(setField1);
}
	
//
//field2()
//gets the first 16 bit field
	
uint16_t CAN_Calibration::field2()
{
	return ((adapterCANPACK_.FULL64BITrxFIELD[4]<<8) | (adapterCANPACK_.FULL64BITrxFIELD[5]));	
}
	
//
//field1(uint16)
//sets the first 16-bit field
	
void CAN_Calibration::field2(uint16_t setField2)
{
	adapterCANPACK_.FULL64BITtxFIELD[4]=(setField2>>8);
	adapterCANPACK_.FULL64BITtxFIELD[5]=(setField2);	
}
	
	
//
//field3()
//gets the first 16 bit field
	
uint16_t CAN_Calibration::field3()
{
	return ((adapterCANPACK_.FULL64BITrxFIELD[6]<<8) | (adapterCANPACK_.FULL64BITrxFIELD[7]));	
}
	
	
//
//field1(uint16)
//sets the first 16-bit field
	
void CAN_Calibration::field3(uint16_t setField3)
{
	adapterCANPACK_.FULL64BITtxFIELD[6]=(setField3>>8);
	adapterCANPACK_.FULL64BITtxFIELD[7]=(setField3);	
}


//
//Recieve_Message();
//
	
void CAN_Calibration::Recieve_Setup()
{
	  //static canMessage::instance()->SetupMOB(CAN_Calibration::adapterCANPACK_.Identity,CAN_Calibration::adapterCANPACK_::direction,CAN_Calibration::adapterCANPACK_::messageDLC);
		canMessage::instance()->SetupMOB(&adapterCANPACK_);
}

//
//constructor()
//

CAN_Calibration::CAN_Calibration(TXorRX setDirection)
{	adapterCANPACK_.Identity = uint16_t((adapterSA_<<8) | (adapterPGN_));
	adapterCANPACK_.messageDLC = adapterDLC_;
	if ((setDirection==BOTH) || (setDirection==RX)){Recieve_Setup();}
	
}

