#ifndef LASTFIX
#define LASTFIX
//#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\GPS_spedometer\CANmessage.cpp>

class canMessage;

class FirstDerivativeMessage  {
	
	public:
	//
	//instance()
	//singleton
	
	static FirstDerivativeMessage* instance();
	
	
	//
	//Velocity()
	//gets the velocity currently set
	
	uint16_t Velocity();
	
	
	//
	//Velocity(uint16)
	//
	
	void Velocity(uint16_t setVelocity);
	
	
	//
	//Heading()
	//gets the heading currently set
	
	uint16_t Heading(); 
	
	
	//
	//Heading(uint16)
	//sets the heading
	
	void Heading(uint16_t setHeading); 
	
	
	//
	//Satellites()
	//returns the number of satellites in view
	
	uint8_t Satellites();
	
	
	//
	//Satellites(uint8)
	//sets the number of satellites in view
	
	void Satellites(uint8_t setSatellites); 
	
	
	//
	//HDOP()
	//returns Horizontal dilution of position
	
	uint8_t HDOP(); 
	
	
	//
	//HDOP(uint8)
	//sets the horizontal dilution of position
	
	void HDOP(uint8_t setHDOP); 
	
	
	//
	//VDOP()
	//returns the vertical dilution of position
	
	uint8_t VDOP(); 
	
	
	//
	//VDOP(uint8)
	//sets the vertical dilution of position
	
	void VDOP(uint8_t setVDOP); 
	
	
	//
	//send()
	//
	
	void Send_Message();
	
	
	canPack adapterCANPACK_;
	
	private:
	
	//
	//constructor
	//
	
	FirstDerivativeMessage();
	
	
	//
	//variables
	//
	
	canMessage *Can_ = canMessage::instance();
	const uint8_t adapterDLC_ = 8;
	const uint8_t adapterSA_=4;     //3 bits
	const uint16_t adapterPGN_=120; //8 bits
	
	uint16_t velocity_; 
	uint16_t heading_; 
	uint8_t satellites_; 
	uint8_t vdop_; 
	uint8_t hdop_; 
	
	
	};
#endif