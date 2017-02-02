/*
 * ADC_Devices.h
 *
 *  Created on: Jun 15, 2015
 *      Author: Jimmy
 */

#ifndef HARDWARE_ADC_DEVICES_H_
#define HARDWARE_ADC_DEVICES_H_

#include <stdint.h>
//#include <avr/io.h>
//#include <avr/iom32m1.h> //TODO TAKE THIS OUT
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\ADCDevicesList.h>


class ADC_Devices{
public:

	//
	//instance()
	//

	static ADC_Devices * instance();


	//
	//uint16_t readNew(SensorList)
	//
	//reads directly from the ADC object

	uint16_t readNew(SensorList adcName);


	//
	//void setupNew(SensorList)
	//
	//sets up the ADC number indicated from the list

	void setupNew(SensorList adcName);


	//
	//void clearCurrent(SensorList)
	//
	//sets the device listed to an outgoing data direction and disables any ADC code

	void clearCurrent(SensorList adcName);


	//
	//uint32_t getActive()
	//
	//returns the active ADC devices bit pack (0 to 31 - mux correct)

	uint32_t getActive();


private:
	//
	//genSetADCHW()
	//
	//activates the general hardware register settings for ADC conversion

	void genSetADCHW();


	//
	//genClearADCHW()
	//
	//clears the general hardware register settings for ADC conversion

	void genClearADCHW();

	//
	//triggerADC(SensorList, ADCMux)
	//
	//returns the actual value after triggering a read

	uint16_t triggerADC(SensorList ADCobj);


	//
	//constructor()
	//

	ADC_Devices();


	uint32_t activeADCBitPack_; //storage location to register/unregister all active ADC devices
};



#endif /* HARDWARE_ADC_DEVICES_H_ */
