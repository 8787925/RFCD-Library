#ifndef TACH_CAL
#define TACH_CAL
#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\eeprom_management.cpp>

class tachometer_cal {
public: 
//
//instance()
//

static tachometer_cal* instance(); 


//
//pulseperK()
//

uint16_t pulseperK(); 


//
//pulseperk(uint16); 
//

void pulseperK(uint16_t ppk);


eeprom_management *eeprom_ = eeprom_management::instance(); //eeprom location
private: 

//
//constructor()
//

tachometer_cal(); 

uint16_t pulses; //pulses current


	};
#endif