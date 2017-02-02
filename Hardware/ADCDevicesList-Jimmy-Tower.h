/*
 * ADCDevicesList.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_ADCDEVICESLIST_H_
#define HARDWARE_ADCDEVICESLIST_H_

//
//ADC_List
//
//List of Mux correct values for ADC Read Enabled Devices

#ifdef __AVR_ATmega32M1__
enum SensorList{ //list of system ADC devices by name and by Mux Value
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC8,
	ADC9,
	ADC10,
	ADCTemp,
	ADCVCCdiv4,
	ADCISRC,
	ADCAmp0,
	ADCAmp1,
	ADCBandGap,
	ADCGnd,
	SPI1,
	SPI2,
	CAN1,
	CAN2,
	UART1,
	UART2
};
#endif


#endif /* HARDWARE_ADCDEVICESLIST_H_ */
