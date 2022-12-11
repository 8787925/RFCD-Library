
#include <Hardware/eeprom_management.h>
#include <avr/eeprom.h>

//
//instance()
//

eeprom_management* eeprom_management::instance()
{
	static eeprom_management theEeprom_management;
	return &theEeprom_management;
}


//
//write(uint8, uint8)
//

void eeprom_management::write_byte(uint16_t address, uint8_t Data)
{
	/* Wait for completion of previous write */
	eeprom_busy_wait(); //while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	this->write(address, &Data, 1);
}


//
//write_block(*src, *dst, size)
//

bool eeprom_management::write(uint16_t address, void* buffer, uint16_t size)
{
	eeprom_update_block(buffer, &address, size_t(size));
}


//
//read_byte(uint16)
//

uint8_t eeprom_management::read_byte(uint16_t address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}


//
//read(address, *data, size)
//

bool eeprom_management::read(uint16_t address, void* buffer, uint16_t size)
{
	eeprom_read_block(buffer, &address, size);
}


//
//constructor
//

eeprom_management::eeprom_management(){};
