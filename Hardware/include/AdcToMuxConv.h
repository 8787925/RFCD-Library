/*
 * AdcToMuxConv.h
 *
 *  Created on: Jun 17, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_ADCTOMUXCONV_H_
#define HARDWARE_ADCTOMUXCONV_H_

enum ADC_List{ //list of system ADC devices by name
	ADC0 = 1,
	ADC1 = 2,
	ADC2 = 4,
	ADC3 = 8,
	ADC4 = 16,
	ADC5 = 32,
	ADC6 = 64,
	ADC7 = 128,
	ADC8 = 256,
	ADC9 = 512,
	ADC10 = 1024,
	ADC11 = 2048,
	ADCTEMP= 0b0001000000000000,
	ADCVCCdiv4= 0b0010000000000000,

};

enum ADCMux{ //LIST OF ADC OBJECTS TO ENACT
	muxADC0 = 0,
	muxADC1,
	muxADC2,
	muxADC3,
	muxADC4,
	muxADC5,
	muxADC6,
	muxADC7,
	muxADC8,
	muxADC9,
	muxADC10,
	muxTempSensor,
	muxVCC_DividedBy_4,
	muxISRC,
	muxAMP0,
	muxAMP1,
	muxBandgap,
	muxGND
};



#endif /* HARDWARE_ADCTOMUXCONV_H_ */
