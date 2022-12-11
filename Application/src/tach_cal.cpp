
#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\tach_cal.h>

#define  TACHOMETER_ADDRESS 0x00
//
//instance()
//

tachometer_cal* tachometer_cal::instance()
{
	static tachometer_cal theTachometer_cal; 
	return& theTachometer_cal; 
}


//
//pulseperK()
//

uint16_t tachometer_cal::pulseperK()
{	
	//if (pulses != 0xffff)
	//{
	///	pulses = (eeprom_->read(TACHOMETER_ADDRESS)<<8);
	//	pulses |= eeprom_->read(TACHOMETER_ADDRESS+1);
		
	//}
	return pulses; 
}


//
//pulseperK(uint16)
//

void tachometer_cal::pulseperK(uint16_t ppk)
{
	if ((ppk!=0xffff) && (pulses!=ppk))
	{
		eeprom_->write(TACHOMETER_ADDRESS,uint8_t(ppk>>8)); 
		eeprom_->write(TACHOMETER_ADDRESS+1,uint8_t(ppk));
		pulses = ppk; 
	}
	
	return; 
}


//
//constructor
//

tachometer_cal::tachometer_cal()
{
	pulses = (eeprom_->read(uint8_t(TACHOMETER_ADDRESS))<<8); 
	pulses |= eeprom_->read(uint8_t(TACHOMETER_ADDRESS+1)); 
}