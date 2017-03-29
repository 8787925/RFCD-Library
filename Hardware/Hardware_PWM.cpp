/*
 * PWM.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: Jimmy
 */
#include "PWM.h"
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Hardware\DeviceTracker.h>
#include <avr/io.h>
#define __AVR_ATmega32M1__
#define CLOCK_0_PRESCALE 1
#define CLOCK_1_PRESCALE 1

	//
	//constructor()
	//
	//constructs by rounding up to the next nearest frequency possible

	PWM::PWM(dacList newPWM, uSeconds period, bool squareFrequencyPWM){
		usingDutyCycle_ = true;
		localOnTime_ = 0;
		countsPerTop_=0xffff;
		uSecondsPerCount = 1000000000; // very high
		localDutyCycle_ = 0;
		activePWMBitPack_=0;
		localHardware_=newPWM;
		localPeriod_= period;
		localRegisterValue_=0x80000000; //impossible value for our counters
		this->setupPWM(newPWM);
	}

	PWM::PWM(dacList newPWM, bool squareFrequencyPWM){
		usingDutyCycle_ = true;
		localOnTime_ = 0;
		countsPerTop_=0xffff;
		uSecondsPerCount = 1000000000; // very high
		localDutyCycle_ = 0;
		activePWMBitPack_=0;
		localHardware_=newPWM;
		localPeriod_= 0;
		localRegisterValue_=0x80000000; //impossible value for our counters
		this->setupPWM(newPWM);
	}


	//
	//setDutyCycle(float)
	//

	void PWM::setDutyCycle(float Percent){
		localRegisterValue_=uint32_t((Percent/100)*countsPerTop_);
	}


	//
	//setuSecondsOn(uSeconds)
	//

	void PWM::setuSecondsOn(uSeconds onTime){

		if (onTime > this->getPeriod()){ //if the time is longer than the period of the clock
			localRegisterValue_ = 0xffff;
			this->localUpdate(localHardware_);}
		else{
			localRegisterValue_ = uint32_t(uSecondsPerCount*onTime);
			this->localUpdate(localHardware_);
			}
	}


	//
	//setupPWM(dacList PWM)
	//
	// responsible for setting up the new pwm object

	void PWM::setupPWM(dacList PWM){

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

		switch (PWM){

		//PWM objects begin with Clock 0, object A
#ifdef __AVR_ATmega32M1__
			//PWM1 OC0A
			case PWM1:
				localPortCheckin.Port_D = (1<<PIND3);
				if (devicePortUse::instance()->checkIn(localPortCheckin)){
					//device is available
					DDRD |= (1<<PIND3);
					TCCR0A |= (1<<COMOA1)
					if (((0x80 & (TCCR0B<<4)) | (0x60 & (TCCR0A<<5))) == 0X30) {
						//FAST PWM, ICR TOP
						countsPerTop_ = 255;
						localPeriod_= (CLOCK_0_PRESCALE * 255) / (F_CPU/1000000);
						uSecondsPerCount = localPeriod_/255;
					}
					activePWMBitPack_ |= (1<<PWM1);
				}
				localPortCheckin.Port_D = 0;
				break;

			//PWM2 OC0B
			case PWM2:
				localPortCheckin.Port_E = (1<<PINE1);
				if (devicePortUse::instance()->checkIn(localPortCheckin)){
					//device is available
					DDRE |= (1<<PINE1);
					TCCR0A |= (1<<COM0B1);
					if (((0x80 & (TCCR0B<<4)) | (0x60 & (TCCR0A<<5))) == 0X30) {
						//FAST PWM, ICR TOP
						countsPerTop_ = 255;
						localPeriod_= (CLOCK_0_PRESCALE * countsPerTop_) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/255;
					}
					activePWMBitPack_ |= (1<<PWM2);
				}
				localPortCheckin.Port_E = 0;
				break;

			//PWM3 OC1A
			case PWM3:
				localPortCheckin.Port_D = (1<<PIND2);
				if (devicePortUse::instance()->checkIn(localPortCheckin)){
					//device is available
					DDRD |= (1<<PIND2);
					TCCR1A |= (1<<COM1A1);
					if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0XE0) {
						//FAST PWM, ICR TOP
						countsPerTop_ = ICR1;
						localPeriod_= (CLOCK_1_PRESCALE * ICR1) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/float(ICR1);
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X50) {
						//FAST PWM, 8 bit top
						countsPerTop_ = 255;
						localPeriod_= (CLOCK_1_PRESCALE * 255) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/255;
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X60) {
						//FAST PWM, 9 bit top
						countsPerTop_ = 511;
						localPeriod_= (CLOCK_1_PRESCALE * 511) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/511;
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X70) {
						//FAST PWM, 9 bit top
						countsPerTop_ = 1023;
						localPeriod_= (CLOCK_1_PRESCALE * 1023) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/1023;
					}

					activePWMBitPack_ |= (1<<PWM3);
				}
				localPortCheckin.Port_D = 0;
				break;

			//PWM4 OC1B
			case PWM4:
				localPortCheckin.Port_C = (1<<PINC1);
				if (devicePortUse::instance()->checkIn(localPortCheckin)){
					//device is available
					DDRC |= (1<<PINC1);
					TCCR1A |= (1<<COM1B1);
					if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0XE0) {
						//FAST PWM, ICR TOP
						countsPerTop_ = ICR1;
						localPeriod_= (CLOCK_1_PRESCALE * ICR1) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/float(ICR1);
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X50) {
						//FAST PWM, 8 bit top
						countsPerTop_ = 255;
						localPeriod_= (CLOCK_1_PRESCALE * 255) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/255;
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X60) {
						//FAST PWM, 9 bit top
						countsPerTop_ = 511;
						localPeriod_= (CLOCK_1_PRESCALE * 511) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/511;
					}
					else if (((0xC0 & (TCCR1B<<3))|(0x30 & (TCCR1A<<4))) == 0X70) {
						//FAST PWM, 9 bit top
						countsPerTop_ = 1023;
						localPeriod_= (CLOCK_1_PRESCALE * 1023) / (F_CPU/1000000);
						uSecondsPerCount = float(localPeriod_)/1023;
					}
					activePWMBitPack_ |= (1<<PWM4);
				}
				localPortCheckin.Port_C = 0;
				break;

			default:
				break;
#endif
		}
	}


	//
	//genClockSetup(dacList PWM)
	//

	void PWM::genClockSetup(dacList Object){

		if ((Object == PWM1) || (Object == PWM2)){
			TCCR0A |= (1<<WGM01) | (1<<WGM00);
#if (CLOCK_0_PRESCALE == 1)
					TCCR0B |= (1<<CS00);
#elif (CLOCK_0_PRESCALE ==8)
					TCCR0B |= (1<<CS01);
#elif (CLOCK_0_PRESCALE ==64)
					TCCR0B |= (1<<CS01) | (1<<CS00);
#elif (CLOCK_0_PRESCALE ==256)
					TCCR0B |= (1<<CS02);
#elif (CLOCK_0_PRESCALE ==1024)
					TCCR0B |= (1<<CS02) | (1<<CS00);
#endif
		}
		else{

#ifndef HARDWARE_LONGCLOCK_H_
			TCCR1A |= (1<<WGM11) | (1<<WGM10);
#if (CLOCK_1_PRESCALE == 1)
					TCCR0B |= (1<<CS00);
#elif (CLOCK_1_PRESCALE ==8)
					TCCR0B |= (1<<CS01);
#elif (CLOCK_1_PRESCALE ==64)
					TCCR0B |= (1<<CS01) | (1<<CS00);
#elif (CLOCK_1_PRESCALE ==256)
					TCCR0B |= (1<<CS02);
#elif (CLOCK_1_PRESCALE ==1024)
					TCCR0B |= (1<<CS02) | (1<<CS00);
#endif
				//adjustment for period
					if ()
#endif
		}
	}

	//
	//localUpdate(dacList PWM);
	//
	//responsible for interacting with the DAC initializer to update the output

	void PWM::localUpdate(dacList PWM){

		if (localRegisterValue_ != 0x80000000){//IF not fault value
			switch (localHardware_){
			case PWM1:
				OCR0A = uint8_t(localRegisterValue_);
				if (TCNT0 > uint16_t(localRegisterValue_)){TCCR0B |= (1<<FOC0A);}
				break;
			case PWM1:
				OCR0B = uint8_t(localRegisterValue_);
				if (TCNT0 > uint16_t(localRegisterValue_)){TCCR0B |= (1<<FOC0B);}
				break;
			case PWM3:
				OCR1A = uint16_t(localRegisterValue_);
				if (TCNT1 > uint16_t(localRegisterValue_)){TCCR1C |= (1<<FOC1A);}
				break;
			case PWM4:
				OCR1B = uint16_t(localRegisterValue_);
				if (TCNT1 > uint16_t(localRegisterValue_)){TCCR1C |= (1<<FOC1B);}
				break;
			}

		}
	}


	//
	//getPeriod()
	//

	uSeconds PWM::getPeriod(){
		return localPeriod_;
	}
