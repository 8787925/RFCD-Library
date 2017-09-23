
#include <eeprom_management.h>
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

void eeprom_management::write(unsigned char address, uint8_t Data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = address;
	EEDR = Data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}


//
//read(uint8)
//

uint8_t eeprom_management::read(uint8_t address)
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
//constructor
//

eeprom_management::eeprom_management(){};
