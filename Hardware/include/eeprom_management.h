#ifndef EEPROM_CAL
#define EEPROM_CAL

#include "config.h"

class eeprom_management 
{
public: 	
//
//instance()
//

static eeprom_management* instance(); 


//
//write()
//

void write_byte(uint16_t address, uint8_t Data);
bool write(uint16_t address, void* buffer, uint16_t size);


//
//read()
//

uint8_t read_byte(uint16_t address);
bool read(uint16_t address, void* buffer, uint16_t size);


private:

//
//constructor
//

eeprom_management();

	};
#endif
