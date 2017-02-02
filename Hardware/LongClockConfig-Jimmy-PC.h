/*
 * clockconfig.h
 *
 *  Created on: Mar 8, 2016
 *      Author: Jimmy
 */

#ifndef HARDWARE_LONGCLOCKCONFIG_H_
#define HARDWARE_LONGCLOCKCONFIG_H_

//#include "C:\Users\Jimmy\OneDrive\Documents\RFCD\MowerProject\config.h"

#include <avr/interrupt.h>
/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

/* Some example here */
//#pragma message(VAR_NAME_VALUE(NOT_DEFINED))
//#pragma message(VAR_NAME_VALUE(DEFINED_BUT_NO_VALUE))

//#pragma message(VAR_NAME_VALUE(DEFINED_STR))

//#define F_CPU 8000000L
#define LONG_CLOCK TCNT1
#define LONG_COUNT_REGISTER (ICR1)
#define U_SECONDS_PER_MATCH RTC_PERIOD_USECONDS
#define LONGCLOCK_PRESCALE 8
#define RTC_ENABLED 1

#define RTC_CLOCK_TOP (((F_CPU*RTC_PERIOD_USECONDS)/(LONGCLOCK_PRESCALE*uSECONDS_PER_SECOND))-1)
#pragma message(VAR_NAME_VALUE(RTC_CLOCK_TOP))
//#if (LONGCLOCK_PRESCALE==1)
// LONG_COUNT_REGISTER = RTC_CLOCK_TOP; TIMSK1 |= (1<<TOIE1);  \//prescale = 1 and CTC on ICR1 match 								  (TCCR1A) |= (1<<WGM11);							  \ //FAST PWM mode
//#endif 			

					  			   
// #ifdef __AVR_ATmega32M1__
// 	//#pragma message ( "ATmega32M1 being used as processor" )
// 	#define LONGCLOCK_REGISTERMAX (65535)
// 	#define COUNTS_PER_TOP ((U_SECONDS_PER_MATCH*(F_CPU/LONGCLOCK_PRESCALE))/1000000)
// 	#define LONGCLOCK_USEC_PERTOP ((1000000*COUNTS_PER_TOP)/(F_CPU/LONGCLOCK_PRESCALE))
// 	#define LONGCLOCK_USEC_PER_COUNT (1000000*(F_CPU/LONGCLOCK_PRESCALE))
// 	#if (COUNTS_PER_TOP > LONGCLOCK_REGISTERMAX)
// 		#error "Register of LongClock exceeds the maximum count"
// 	#endif
// 
// 	#if (LONGCLOCK_PRESCALE==1)
// 		#define longClock_Init()  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);  \ //prescale = 1 and CTC on ICR1 match
// 								  (TCCR1A) |= (1<<WGM11);							  \ //FAST PWM mode
// 								  LONG_COUNT_REGISTER = RTC_CLOCK_TOP;			  \ //TOP is as calculated
// 								  TIMSK1 |= (1<<TOIE1)								//enable interrupt
// 								  
// 	#elif (LONGCLOCK_PRESCALE==8)
// 		#define longClock_Init()  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11);  \
// 								  TIMSK1 |= (1<<TOIE1); \
// 								  TCCR1A |= (1<<WGM11); \
// 								  LONG_COUNT_REGISTER = RTC_CLOCK_TOP;
// 
// 	#elif (LONGCLOCK_PRESCALE==64)
// 		#define longClock_Init() {TCCR1B |= (1<<CS11) | (1<<CS10);  \
// 								  TIMSK1 |= (1<<TOIE1); }
// 	#elif (LONGCLOCK_PRESCALE==256)
// 		#define longClock_Init() {TCCR1B |= (1<<CS12);  \
// 								  TIMSK1 |= (1<<TOIE1); }
// 	#elif (LONGCLOCK_PRESCALE==1024)
// 		#define longClock_Init() {TCCR1B |= (1<<CS12) | (1<<CS10);  \
// 								  TIMSK1 |= (1<<TOIE1); }
// 	#endif
// 
// 	#if (RTC_ENABLED)
// 
// 	#endif
// #endif




#endif /* HARDWARE_LONGCLOCKCONFIG_H_ */
