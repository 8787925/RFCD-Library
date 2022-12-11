/*
 * PID_Fixed.h
 *
 *  Created on: Jun 15, 2015
 *      Author: Jimmy
 */

#ifndef PID_KIT_H_
#define PID_KIT_H_

//#include <C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\avr\include\stdint.h>
//#include <C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\avr\include\math.h>
#include <math.h>
//#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\Sensor.h>
//#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Timer.h>
//#include <avr/include/math.h>


template <class T>
class PIDkit {
public:
	//
	//constructor(T, T, T)
	//

	PIDkit(T pGain, T iGain, T dGain, T initialCondition, T updatePeriod, T updatePeriodFactor)
	{
		pGain_ = pGain;
		iGain_ = iGain;
		dGain_ = dGain;
		updateRate_ = updatePeriod;
		updateRateTypeFactor_ = updatePeriodFactor;
		dtOkToUse_ = false;
		initialCondition_ = initialCondition;
		hasRateTypeFactor_ = true;
	};

	PIDkit(T pGain, T iGain, T dGain, T initialCondition, T updatePeriod)
	{
		pGain_ = pGain;
		iGain_ = iGain;
		dGain_ = dGain;
		updateRate_ = updatePeriod;
		updateRateTypeFactor_ = T(1);
		dtOkToUse_ = false;
		initialCondition_ = initialCondition;
		hasRateTypeFactor_ = false;
	};


	//
	//update(T reading)
	//

	T update(T reading)
	{
		this->updateError(reading);

		//
		//Kp Calculation
		//

		if (pGain_ != T(0))
		{
			//p value calculation
			pValue_ = pGain_*error_;
		}
		else
		{
			pValue_ = 0;
		}

		//
		//Ki Calculation
		//

		if ((iGain_ != T(0)) && (dtOkToUse_))
		{
			//i value calculation
			//uses trapezoidal integral between stored value and current error
			if (hasRateTypeFactor_)
			{
				iValue_ += ((error_ - ((error_ - error_Zero_)/2))*updateRate_) / updateRateTypeFactor_;
			}
			else
			{
				iValue_ += ((error_ - ((error_ - error_Zero_)/2))*updateRate_);
			}

		}
		else
		{
			iValue_ = 0;
		}

		//
		//Kd Calculation
		//

		if ((dGain_ != T(0)) && (dtOkToUse_))
		{
			//d value calculation
			if (hasRateTypeFactor_)
			{
				dValue_ = (updateRateTypeFactor_*(error_-error_Zero_))/updateRate_;
			}
			else
			{
				dValue_ = (error_-error_Zero_)/updateRate_;
			}

		}
		else
		{
			dValue_ = 0;
		}

		error_Zero_ = error_; //store the last value of Error for use in the dT that will be used.
		dtOkToUse_ = true;
		result_ = pValue_ + iValue_ + dValue_;
		return result_;
	};


	//
	//setUpdateRate(T)
	//

	void setUpdateRate(T updateRate){updateRate_ = updateRate;};
	T getUpdatRate(){return updateRate_;};


	//
	//setSetPoint(int16_t)
	//
	//changes the setpoint of the loop

	void setSetPoint(T newSetPoint){setPoint_ = newSetPoint;};
	T getSetPoint(){return setPoint_;};


	//
	//getError()
	//
	//returns the error of the PID, differenced between the Target and the signal

	T getError(){return error_;};


	//
	//getPValue()
	//
	//returns the P contribution to the output

	T getPValue(){return pValue_;};


	//
	//getIValue()
	//
	//returns the I contribution to the output

	T getIValue(){return iValue_;};


	//
	//getDValue()
	//
	//returns the D contribution to the output

	T getDValue(){return dValue_;};


	//
	//setPGain(T)
	//

	void setPGain(T gain){pGain_ = gain;};
	T getPGain(){return pGain_;};


	//
	//setIGain(T)
	//

	void setIGain(T gain){iGain_ = gain;};
	T getIGain(){return iGain_;};


	//
	//setDGain(T)
	//

	void setDGain(T gain){dGain_ = gain;};
	T getDGain(){return dGain_;};


	//
	//setSaturationUpper(T)
	//

	void setISaturationUpper(T saturation)
	{
		if (iValue_ > saturation)
		{
			iValue_ = saturation;
		}

		iSaturationUpper_ = saturation;
	};

	T getISaturationUpper(){return iSaturationUpper_;};


	//
	//setSaturationLower(T)
	//

	void setISaturationLower(T saturation)
	{
		if (iValue_ < saturation)
		{
			iValue_ = saturation;
		}

		iSaturationLower_=saturation;
	};

	T setISaturationLower(){return iSaturationLower_;};


	//
	//setInitialCondition(T)
	//

	void setInitialCondition(T initial){initialCondition_ = initial;};
	T getInitialCondition(){return initialCondition_;};


	//
	//resetIntegrator();
	//

	void resetIntegrator(){iValue_ = 0;};

private:

	//
	//updateError(T)
	//

	void updateError(T reading)
	{
		reading_ = reading;
		error_ = reading_-setPoint_;
	};


	//
	//variables
	//

	T pGain_;
	T iGain_;
	T dGain_;
	T pValue_;
	T iValue_;
	T dValue_;
	T iSaturationUpper_;
	T iSaturationLower_;
	T sensorReadingZeroValue_;
	T initialCondition_;
	T setPoint_;
	T reading_;
	T error_;
	T error_Zero_;
	T result_;
	T updateRate_;
	T updateRateTypeFactor_;
	bool hasRateTypeFactor_;
	bool dtOkToUse_;

};


#endif /* PID_KIT_H_ */
