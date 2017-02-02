/*
 * Engine.h
 *
 *  Created on: May 3, 2016
 *      Author: Jimmy
 */

#ifndef APPLICATION_ENGINE_H_
#define APPLICATION_ENGINE_H_

#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\PID.h>	//control loop for eng speed
#include <C:\Users\Jimmy\OneDrive\Documents\RFCD\Code Libraries\Application\Servo.h>		//actuator for carburator

enum EngineControlMode {
	SpeedControl,
	LoadControl
};

enum EngineState {
	PreCheck,			//engine is in power-on and performing pre-checks/loads
	Off,				//engine is at 0 speed
	Starting,			//engine is not at idle and is attempting to ascend to idle
	Idle, 				//engine is ready to respond to commands but is not being requested to execute
	Responding,			//engine is responding to control requests
	EngineProtection, 	//reserved for rev limiting and faults - indicates engine control is no longer directly from requests
	EngineProtectionShutDown //engine has been shut down after protection invokation
};

enum EngineProtectionReason {
	None,				//engine is not in protection
	RevLimitUpper, 		//engine has exceeded maximum speed limit, and is being restricted to prevent damage
	TemperatureUpper,	//upper temperature threshold has been exceeded and is now being derated
	TemperatureLower, 	//lower temperature threshold for work hasn't been reached
	Unknown				//state that captures all remaining fault cases
};

struct CarburatorCalibrationSet{
	float throttleActuatorUpperLimit; 	//percentage maximum for throttle actuator
	float throttleActuatorLowerLimit;	//percentage minimum for the throttle actuator
	uSeconds expectedResponseTime;		//time, after which if the throttle fails to respond, a fault sets
};

struct EngineCalibrationSet{
	uint16_t IdleSpeed;					//idle target speed
	uint16_t RevLimitUpper;				//upper engine speed before protection
	float LoadLimit;					//load percentage maximum permitted
	float degFLimitUpper;				//engine temperature permitted maximum before inhibited engine operations
	float degFLimitLower;				//engine temperature permitted minimum before uninhibited operations
	PIDDataTable SpeedControlPID;		//engine speed/load control PID
	uint16_t EngineRunHours;			//engine runtime 1hr/bit
	CarburatorCalibrationSet Carburator;//engine carburator calibrations
};

class Engine{

	//
	//setSpeed(uint16)
	//
	//sets the engine target speed

	void setSpeed(uint16_t Speed);
	void setSpeed(float Speed);
	uint16_t getSpeed();


	//
	//setPercentLoad(float)
	//
	//sets the engine load percent feed forward

	void setPercentLoad(float Percent);
	float getPercentLoad();


	//
	//setControlMode(enum)
	//
	//sets the engine control mode

	void setControlMode(EngineControlMode ControlMode);
	EngineControlMode getControlMode();


	//
	//getEngineState()
	//
	//responds with the engines current operating state

	EngineState getEngineState();


	//
	//ShutDown()
	//
	//Request to stop the engine, sets 'unknown' engine protection state

	bool ShutDown();


	//
	//reasonForProtection()
	//
	//responds with the enum of reasons the engine is in protection mode

	EngineProtectionReason reasonForProtection();


	//
	//getEngineHours()
	//
	//responds with the total stored engine run time in hours

	uint16_t getEngineHours();


	//
	//Engine()
	//
	//constructor

	Engine(EngineCalibrationSet& engineCalSet);


	//
	//update()
	//
	//engine's loop handle

	void update();


private:

	//
	//state()
	//
	//updates the engine's current stored state

	void state();


	//
	//diag()
	//
	//future use for diagnostics

	EngineProtectionReason diag();


	//
	//variables
	//

	EngineState EngineState_; 						//locally stored engine state
	EngineProtectionReason EngineProtectionReason_; //locally stored engine protection reason
	EngineControlMode EngineControlMode_;			//locally stored engine control mode
	EngineCalibrationSet *EngineCalibrationSet_;		//locally stored engine calibration
};



#endif /* APPLICATION_ENGINE_H_ */
