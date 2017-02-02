#ifndef SPI_TRANSACTION
#define  SPI_TRANSACTION

enum SPIdevice{
	SPI1,
	SPI2,
	SPI3,
	SPI4
};

class Spi1Transaction{
	public: 
	
	//
	//instance()
	//
	
	static Spi1Transaction* instance();
	
	
	//
	//initialize(uint8 baud)
	//
	
	void initialize(uint8_t baud);
	
	
	//
	//void send(uint8 Data)
	//
	
	void send(uint8_t Data);
	
	
	//
	//uint8 receive();
	//
	
	uint16_t receive();
	
	private: 
	//
	//constructor()
	//
	
	Spi1Transaction();
	};
#endif
