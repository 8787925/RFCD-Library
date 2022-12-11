#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\WaterInjector\WaterInjector\WaterInjector\SPI_Transaction.h"


//
//instance()
//

Spi1Transaction* Spi1Transaction::instance()
{
	static Spi1Transaction theSpi1Transaction;
	return &theSpi1Transaction;
}


//
//send(uint8 Data)
//

void Spi1Transaction::send(uint8_t Data)
{
	uint16_t iwannacount;
	
	/* Start transmission */
	
	PORTE &= !(1<<PINE1); // set AND HOLD the ss pin LOW  to trigger the receive TODO THIS PIN CHANGES IN NEW HARDWARE
	SPDR = Data;
	
	/* Wait for transmission complete */
	
	iwannacount=0;
	while(!(SPSR & (1<<SPIF))) 
	{
		
		iwannacount+=1;
		if (iwannacount>2000)
		{
			//PORTC |= (LEDOFF<<SPIACTIVITYLED); //SHUT OFF THE INDICATOR LED
			PORTE |= (1<<PINE1); //RETURN THE CS TO NORMAL STATE
			return;//PORTC &= !(LEDON<<SPIACTIVITYLED);
		}
	}
	PORTE |= (1<<PINE1);
	return;
}


//
//uint8 recieve()
//

uint16_t Spi1Transaction::receive()
{	uint8_t cData = 0xFF;
	
	if (/*relayobject.status()*/)
	{cData=0xFF;} //nothing in this data packet (shift in 8 zeros, to not disturb the port function), TODO THIS IS A PATCH FOR BAD HARDWARE
	else
	{cData=0;}
	
	
	uint16_t iwannacount;
	uint16_t ThermTemp;
	ThermTemp = 0; //initialize the thermo value
	
	/* Start transmission */
		
	PORTE &= !(1<<PINE1); // set AND HOLD the ss pin LOW  to trigger the receive TODO THIS PIN CHANGES IN NEW HARDWARE
	SPDR = cData;
	
	/* Wait for transmission complete */
	iwannacount=0;
	while(!(SPSR & (1<<SPIF))) {
		//PORTC |= (LEDON<<SPIACTIVITYLED);
		iwannacount+=1;//PORTC &= !(LEDON<<SPIACTIVITYLED);//while the flag isn't set
		if (iwannacount>2000){
			//PORTC |= (LEDOFF<<SPIACTIVITYLED); //SHUT OFF THE INDICATOR LED
			PORTE |= (1<<PINE1); //RETURN THE CS TO NORMAL STATE
			return 0xdd;//PORTC &= !(LEDON<<SPIACTIVITYLED);
		}//PORTC &= !(LEDON<<SPIACTIVITYLED);}
	}
	//cData=0xff;
	//sp3=SPSR;
	ThermTemp = (SPDR<<8); //shift the first 8 bits to the left of the variable
	//sp2=SPSR;
	//if (!(SPSR & (1<<SPIF))){ //if the flag isn't set
	SPDR = cData;// write dummy data again if the flag has indeed cleared
	//}
	//else { return 0x00;}//get out if it didn't set
	//if ((SPSR & (1<<SPIF))){return 0x00;}// if the flag is set
	
	//_delay_ms(1);
	//PORTC |= (1<<SPIACTIVITYLED); //TURN THE LIGHT OFF
	//sp2=SPSR;
	iwannacount=0;
	while(!(SPSR & (1<<SPIF))){PORTC |=(LEDON<<SPIACTIVITYLED);
		iwannacount+=1;//PORTC &= !(LEDON<<SPIACTIVITYLED);//while the flag isn't set
		if (iwannacount>2000){
			//PORTC |= (LEDOFF<<SPIACTIVITYLED); //SHUT OFF THE INDICATOR LED
			PORTE |= (1<<PINE1); //RETURN THE CS TO NORMAL STATE
		return 0;}
	}
	ThermTemp |= SPDR;
	PORTE |=(1<<PINE1); // set the pin low to shut off the rx
	ThermTemp = (ThermTemp>>3); //the right 3 bits are for chip info, and are not usable signal.

	//PORTC |= (LEDOFF<<SPIACTIVITYLED); //TURN THE LIGHT OFF
	//if (!(SPSR & (1<<SPIF))){PORTC |= (LEDOFF<<SPIACTIVITYLED);
	return ThermTemp;//} //if the port is, in fact, cleared properly
	//else { PORTC &= !(LEDON<<SPIACTIVITYLED);
	//return 0x0;}
}


//
//initialize(uint8 Baud)
//

void Spi1Transaction::initialize(uint8_t baud)
{
	//DDRC|= (LEDON<<SPIACTIVITYLED);
	/* Set MOSI and SCK output, all others input */

	//DDRB = 0x00;
	//DDRD = 0x00;
	DDRB &= !(1<<PINB0); // SET THE MISO AS AN INPUT (0)
	DDRB |= (0<<PINB1) | (1<<PINB7);// MOSI | SCK pin AS OUTPUTS (1) TODO PINB1 FOR NOW IS GOING TO BE GOVERNED BY THE RELAY LOGIC. IT SHOULD BE CHANGED.
	DDRE |= (1<<PINE1);//ss pin AS OUTPUT (1)
	//DDRD |= (1<<PIND3);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)| (0<<SPR1) | (1<<SPR0); //ENABLE SPI | SET AS MASTER | PRESCALE TO 16fck
}