/*
 * ADC_Devices.cpp
 *
 *  Created on: Jun 15, 2015
 *      Author: Jimmy
 */


#include <avr/io.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADC_Devices.h>
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\DeviceTracker.h>


//
//instance()
//

ADC_Devices * ADC_Devices::instance(){
	static ADC_Devices theADC_Devices;
	return &theADC_Devices;
}


//
//constructor()
//

ADC_Devices::ADC_Devices(){activeADCBitPack_ = 0;}


//
//uint16_t readNew(SensorList)
//

uint16_t ADC_Devices::readNew(ADCResource adcName){

	if (activeADCBitPack_ & (1<<adcName)){//if the device is active
		return this->triggerADC(adcName);
	}
	return (1<<15);//return if inactive - impossible reading for the 10-bit device
}


//
//uint8_t getActive()
//

uint32_t ADC_Devices::getActive(){
	return activeADCBitPack_;
}


//
//genSetADCHW()
//

void ADC_Devices::genSetADCHW(){

#ifdef __AVR_ATmega32M1__
	ADMUX |= (1<<REFS0); //AVcc for voltage reference
	ADCSRA |= (1<<ADEN) | (2<<ADPS0); //Enable ADC | ADC prescale = (clock/(2^value))
	ADCSRB |= (1<<ADHSM); //High speed conversion clock (greather than 200kHz)
#endif

}


//
//genClearADCHW()
//

void ADC_Devices::genClearADCHW(){

#ifdef __AVR_ATmega32M1__
	ADMUX &= ~(1<<REFS0);
	ADCSRA &= ~((1<<ADEN) | (2<<ADPS0));
	ADCSRB &= ~(1<<ADHSM);
#endif
}


//
//clearCurrent(SensorList)
//

void ADC_Devices::clearCurrent(ADCResource adcName){

	if (activeADCBitPack_ & (1<<adcName)){ //if the device is active
		activeADCBitPack_ = (activeADCBitPack_ & uint16_t(~(1<<adcName))); //maybe should just be -= adcName?
	}
	if (activeADCBitPack_ == 0) {this->genClearADCHW();} //if all devices are inactive, stop ADC Setup
	return;

}


//
//setupNew(SensorList)
//

void ADC_Devices::setupNew(ADCResource adcName){

	Ports localPortCheckin;
	localPortCheckin.Port_A = 0;
	localPortCheckin.Port_B = 0;
	localPortCheckin.Port_C = 0;
	localPortCheckin.Port_D = 0;
	localPortCheckin.Port_E = 0;
	localPortCheckin.Port_F = 0;
	localPortCheckin.Port_G = 0;
	localPortCheckin.Port_H = 0;
	localPortCheckin.Port_I = 0;

	if (activeADCBitPack_ & adcName){ return;}//if it's already active
#ifdef __AVR_ATmega32M1__

		switch (adcName) {

		//ADC0
		case ADC0:
			localPortCheckin.Port_E = (1<<PINE2);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){ //device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC0D);
				activeADCBitPack_ |= (1<<adcName);
				DDRE &= ~(1<<PINE2);
			}
			localPortCheckin.Port_E = 0;
			break;

		//ADC1
		case ADC1:
			localPortCheckin.Port_D = (1<<PIND4);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC1D);
				activeADCBitPack_ |= (1<<adcName);
				DDRD &= ~(1<<PIND4);
			}
			localPortCheckin.Port_D = 0;
			break;

		//ADC2
		case ADC2:
			localPortCheckin.Port_D = (1<<PIND5);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC2D);
				activeADCBitPack_ |= (1<<adcName);
				DDRD &= ~(1<<PIND5);
			}
			localPortCheckin.Port_D = 0;
			break;

		//ADC3
		case ADC3:
			localPortCheckin.Port_D = (1<<PIND6);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC3D);
				activeADCBitPack_ |= (1<<adcName);
				DDRD &= ~(1<<PIND6);
			}
			localPortCheckin.Port_D = 0;
			break;

		//ADC4
		case ADC4:
			localPortCheckin.Port_B = (1<<PINB7);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC4D);
				activeADCBitPack_ |= (1<<adcName);
				DDRB &= ~(1<<PINB7);
			}
			localPortCheckin.Port_B = 0;
			break;

		//ADC5
		case ADC5:
			localPortCheckin.Port_B = (1<<PINB2);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC5D);
				activeADCBitPack_ |= (1<<adcName);
				DDRB &= ~(1<<PINB2);
			}
			localPortCheckin.Port_B = 0;
			break;

		//ADC6
		case ADC6:
			localPortCheckin.Port_B = (1<<PINB5);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC6D);
				activeADCBitPack_ |= (1<<ADC6);
				DDRB &= ~(1<<PINB5);
			}
			localPortCheckin.Port_B = 0;
			break;

		//ADC7
		case ADC7:
			localPortCheckin.Port_B = (1<<PINB6);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR0 |= (1<<ADC7D);
				activeADCBitPack_ |= (1<<adcName);
				DDRB &= ~(1<<PINB6);
			}
			localPortCheckin.Port_B = 0;
			break;

		//ADC8
		case ADC8:
			localPortCheckin.Port_C = (1<<PINC4);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR1 |= (1<<ADC8D);
				activeADCBitPack_ |= (1<<adcName);
				DDRC &= ~(1<<PINC4);
			}
			localPortCheckin.Port_C = 0;
			break;

		//ADC9
		case ADC9:
			localPortCheckin.Port_C = (1<<PINC5);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR1 |= (1<<ADC9D);
				activeADCBitPack_ |= (1<<adcName);
				DDRC &= ~(1<<PINC5);
			}
			localPortCheckin.Port_C = 0;
			break;

		//ADC10
		case ADC10:
			localPortCheckin.Port_C = (1<<PINC6);
			if (devicePortUse::instance()->checkOut(localPortCheckin)){//the device is available
				this->genSetADCHW();
				DIDR1 |= (1<<ADC10D);
				activeADCBitPack_ |= (1<<adcName);
				DDRC &= ~(1<<PINC6);
			}
			localPortCheckin.Port_C = 0;
			break;

		//SPI/CAN/UART
		//case > ADCGnd:
		//	break;

		//ALL OTHER ADC (non-pin)
		default:
			this->genSetADCHW();
			activeADCBitPack_ |= (1<<adcName);
			break;
		}
#endif
}


//
//triggerADC(SensorList,ADCMux)
//

uint16_t ADC_Devices::triggerADC(ADCResource ADCobj){
	uint16_t temp = 0;
	ADMUX &= (0b11100000); //clear the MUX content
	ADMUX |= uint8_t(ADCobj); //insert the new Mux
	ADCSRA|= (1<<ADSC); //Start ADC Conversion

	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA &= 0xff; //clear interrupt flag by writing 1 to it.
	temp |= ADCL;
	temp |= (ADCH<<8);
	return uint16_t(temp);// (ADCH<<8) | (ADCL) ); //Return the high and low register
}
