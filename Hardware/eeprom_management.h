#ifndef EEPROM_CAL
#define EEPROM_CAL

class eeprom_management 
{
public: 	
//
//instance()
//

static eeprom_management* instance(); 


//
//write(uint16)
//

void write(unsigned char address, uint8_t Data);


//
//read(uint16)
//

uint8_t read(uint8_t address); 
private:

//
//constructor
//

eeprom_management();

	};
#endif