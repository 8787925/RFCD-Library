#ifndef CAN_CAL
#define CAN_CAL
//#include <C:\Users\Jimmy\OneDrive\Documents\Atmel Studio\6.1\GPS_spedometer\GPS_spedometer\CANmessage.cpp>

class canMessage;

class CAN_Calibration  {
	
	public:
	//
	//instance()
	//singleton
	
	static CAN_Calibration* instance(TXorRX setDirection);
	
	
	//
	//Parameter()
	//gets the velocity currently set
	
	uint16_t Parameter();
	
	
	//
	//Parameter(uint16)
	//
	
	void Parameter(uint16_t setParameter);
	
	
	//
	//field1()
	//gets the first 16 bit field
	
	uint16_t field1();
	
	
	//
	//field1(uint16)
	//sets the first 16-bit field
	
	void field1(uint16_t setField1);
	
	//
	//field2()
	//gets the first 16 bit field
	
	uint16_t field2();
	
	
	//
	//field1(uint16)
	//sets the first 16-bit field
	
	void field2(uint16_t setField2);
	
	
	//
	//field3()
	//gets the first 16 bit field
	
	uint16_t field3();
	
	
	//
	//field1(uint16)
	//sets the first 16-bit field
	
	void field3(uint16_t setField3);
	
	
	//
	//send()
	//
	
	void Send_Message();
	
	

	
	private:
	//
	//constructor
	//
	
	CAN_Calibration(TXorRX setDirection);
	
	
	//
	//Recieve_Message();
	//
		
	void Recieve_Setup();
	
	
	//
	//variables
	//
	
	canMessage *Can_ = canMessage::instance();
	uint8_t adapterDLC_ = 8;
	uint8_t adapterSA_=5;     //3 bits
	uint16_t adapterPGN_=121; //8 bits
	canPack adapterCANPACK_;
};
#endif