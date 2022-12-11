/*
 * ADC_Sensor.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: Jimmy
 */

#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC_Sensor.h"

//
//constructor
//

ADC_Sensor::ADC_Sensor(ADCResource SensorUsed)
{
	readingDevice_ = SensorUsed;
	
	ADMUX |= (1<<REFS0); //AVcc for voltage reference
	ADCSRA |= (1<<ADEN) | (2<<ADPS0); //Enable ADC | ADC prescale = (clock/(2^value))
	ADCSRB |= (1<<ADHSM); //High speed conversion clock (greather than 200kHz)

}


//
//readRaw()
//

uint16_t ADC_Sensor::readRaw()
{
	uint16_t temp = 0;
	ADMUX &= (0b11100000); //clear the MUX content
	ADMUX |= uint8_t(readingDevice_); //insert the new Mux
	ADCSRA|= (1<<ADSC); //Start ADC Conversion
	//ADCSRA &= 0xff; //clear interrupt flag by writing 1 to it
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA &= ~(1<<ADSC); //clear interrupt flag by writing 1 to it.
	temp |= ADCL;
	temp |= (ADCH<<8);
	this->insertReading(temp);
	return uint16_t(temp);// (ADCH<<8) | (ADCL) ); //Return the high and low register
}


//
//getReading()
//

uint16_t ADC_Sensor::getReading()
{
	return (gain_ * this->storedReading_) + offset_;
}


//
//enable()
//

void ADC_Sensor::enable()
{
#ifdef __AVR_ATmega32M1__
	switch (readingDevice_)
	{
	case ADC0:
		DDRE &= ~(1<<PINE2);
		break;
	case ADC1:
		DDRD &= ~(1<<PIND4);
		break;
	case ADC2:
		DDRD &= ~(1<<PIND5);
		break;
	case ADC3:
		DDRD &= ~(1<<PIND6);
		break;
	case ADC4:
		DDRB &= ~(1<<PINB7);
		break;
	case ADC5:
		DDRB &= ~(1<<PINB2);
		break;
	case ADC6:
		DDRB &= ~(1<<PINB5);
		break;
	case ADC7:
		DDRB &= ~(1<<PINB6);
		break;
	case ADC8:
		DDRC &= ~(1<<PINC4);
		break;
	case ADC9:
		DDRC &= ~(1<<PINC5);
		break;
	case ADC10:
		DDRC &= ~(1<<PINC6);
		break;
	case ADCTemp:
	break;

	case ADCVCCdiv4:
	break;

	case ADCISRC:
	break;

	case ADCAmp0:
		DDRB &= ~((1<<PINB4) | (1<<PINB3));
		break;
	case ADCAmp1:
		DDRC &= ~((1<<PINC4) | (1<<PINC5));
		break;
	case ADCBandGap:
	break;

	case ADCGnd:
	break;

	default:
	break;
	}
#endif

}


//
//disable()
//

void ADC_Sensor::disable()
{

}


//
//remove()
//

void ADC_Sensor::remove()
{

}
