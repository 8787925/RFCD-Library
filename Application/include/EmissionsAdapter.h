#ifndef EMISSIONS_ADAPTER
#define EMISSIONS_ADAPTER

enum ThreeStateRequest{
	True,
	False,
	Passive
	};
class EmissionsAdapter
{
	
	public:
	//
	//instance()
	//singleton
	
	static EmissionsAdapter * instance();
	
	
	//
	//waterMotorRequest()
	//requests the water injector motor be set to on
	
	uint8_t waterMotorRequest();
	
	
	//
	//waterMotorRequest(bool)
	//gets the velocity currently set
	
	void waterMotorRequest(bool Status);
	
	
	//
	//waterMotorStatus()
	//gets the velocity currently set
	
	bool waterMotorStatus();
	
	
	//
	//waterMotorStatus()
	//gets the velocity currently set
	
	void waterMotorStatus(bool Status);
	
	
	//
	//EGT()
	//exhaust gas temp currently set
	
	uint16_t EGT();
	
	
	//
	//EGT(uint16)
	//sets the exhaust gas temp
	
	void EGT(uint16_t Temperature);
	
	
	//
	//waterPressure()
	//gets the water pressure currently set
	//0.05 kPa per bit
	
	uint16_t waterPressure();
	
	
	//
	//field1(uint16)
	//sets the first 16-bit field
	//0.05 kPa per bit
	
	void waterPressure(uint16_t Pressure_kPa);
	
	
	//
	//send()
	//
	
	void Send_Message();
	
	

	
	private:
	//
	//constructor
	//
	
	EmissionsAdapter(TXorRX setDirection);
	
	
	//
	//Recieve_Message();
	//
	
	void Recieve_Setup();
	
	
	//
	//variables
	//
	
	canMessage *Can_ = canMessage::instance();
	uint8_t adapterDLC_ = 8;
	uint8_t adapterSA_= CAN_SA;     //3 bits
	uint16_t adapterPGN_=122; //8 bits
	canPack adapterCANPACK_;
};
};
#endif
