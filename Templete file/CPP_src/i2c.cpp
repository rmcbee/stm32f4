#include "i2c.h"
#include <cstdarg>


//test the new bit of code in the write function


i2c::i2c(GPIO_TypeDef* sclBank, uint16_t scl_pin, GPIO_TypeDef* sdaBank, uint16_t sda_pin, I2C_TypeDef*  selected_I2C, uint64_t frequency , uint8_t id)
{
	I2Cx = selected_I2C;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	
	// enables the I2C clock
	i2c_bankToClcok( I2Cx);
	
	
	
	// enables the clocks for the scl/sda banks
	bankToClock(sclBank);
	bankToClock(sdaBank);
	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			// set pins to alternate function
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		// set output to open drain --> the line has to be only pulled low, not driven high
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		// set GPIO speed
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			// enable pull up resistors
	
	
	
	//initilize scl
	GPIO_InitStruct.GPIO_Pin = scl_pin;					// sets the pin being initialized
	GPIO_Init(sclBank, &GPIO_InitStruct);				// initializes the pin for alternate functions
	
	//initilize sdc
	GPIO_InitStruct.GPIO_Pin = sda_pin;				// sets the pin being initialized
	GPIO_Init(sdaBank, &GPIO_InitStruct);				// initializes the pin for alternate functions
	
	
	// Connect pins to AF  
	GPIO_PinAFConfig(sclBank, getPinSource(scl_pin), getAlternateFunction(I2Cx));	// SCL
	GPIO_PinAFConfig(sdaBank,  getPinSource(sda_pin), getAlternateFunction(I2Cx)); // SDA
	
	
	
	
	// configure I2C1 
	I2C_InitStruct.I2C_ClockSpeed = frequency; 		// sets the frequency
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;			// I2C mode
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;	// 50% duty cycle --> standard
	I2C_InitStruct.I2C_OwnAddress1 = id;			// own address, not relevant in master mode
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;		// disable acknowledge when reading (can be changed later on)
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // set address length to 7 bit addresses
	I2C_Init(I2Cx, &I2C_InitStruct);				// init I2C1
	
	// enable I2C1
	I2C_Cmd(I2Cx, ENABLE);
}

void i2c::write(uint8_t address, uint8_t num, ... ) 
{
	
	start(address << 1, I2C_Direction_Transmitter);  //bit shifts the address and sends the address and that we will be writing

	va_list arguments; // A place to store the list of arguments
	
	va_start(arguments, num); //stores the variables from the argument line into the variable
	
	//loops through each piece of data and prints it
	for(int i = 0; i < num; i++)
	{
		I2C_SendData(I2Cx, (uint8_t) va_arg(arguments, int) );
		// wait for I2C1 EV8_2 --> byte has been transmitted
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	
	//cleans up the memory from the variable
	va_end(arguments);
	
	// Send I2C1 STOP Condition 
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

uint8_t i2c::readAck(uint8_t address)
{
	if(startedReading == false)
	{
		start(address << 1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
		
		//changes the variable to indicate that reading has started
		startedReading = true;
	}
	
	// enable acknowledge of recieved data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;	
}

uint8_t i2c::readNack()
{
	
	
	// disabe acknowledge of received data
	// nack also generates stop condition after last byte received
	// see reference manual for more info
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	
	//triggers the I2C to stop transmitting
	I2C_GenerateSTOP(I2Cx, ENABLE);
	startedReading = false;  //resets the variable to false to indicate that no reading is happening
	
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}


void i2c::start(uint8_t address, uint8_t direction)
{
	// wait until I2C1 is not busy anymore
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  
	// Send I2C1 START condition 
	I2C_GenerateSTART(I2Cx, ENABLE);
	  
	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
		
	// Send slave Address for write 
	I2C_Send7bitAddress(I2Cx, address, direction);
	  
	/* wait for I2C1 EV6, check if 
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */ 
	if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

void i2c::i2c_bankToClcok(I2C_TypeDef*  I2Cx)
{
	if (I2Cx == I2C1)
	{
	    /* Enable I2C1 clock */
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 
	}
	else if (I2Cx == I2C2)
	{
	    /* Enable I2C2 clock */
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE); 
	}
	else if (I2Cx == I2C3)
	{
	      /* Enable I2C3 clcok */
	     RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE); 
	}
}

uint8_t i2c::getAlternateFunction(I2C_TypeDef*  I2Cx)
{
	if (I2Cx == I2C1)
	{
	    return GPIO_AF_I2C1;
	}
	else if (I2Cx == I2C2)
	{
	    return GPIO_AF_I2C2;
	}
	else if (I2Cx == I2C3)
	{
	      return GPIO_AF_I2C3; 
	}
}

void i2c::bankToClock(GPIO_TypeDef* bank)
{
	
	//initializes the correct clock that goes with the inputed bank
	if (bank == GPIOA)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	}
	else if (bank == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	else if (bank == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  	}
	else if (bank == GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	}
	else if (bank == GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	}
	else if (bank == GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	}
	else if (bank == GPIOG)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	}
}

uint16_t i2c::getPinSource(uint16_t pin)
{
	if(pin == GPIO_Pin_0)
	{
		return GPIO_PinSource0;
	}
	else if(pin == GPIO_Pin_1)
	{
		return GPIO_PinSource1;
	}
	else if(pin == GPIO_Pin_2)
	{
		return GPIO_PinSource2;
	}
	else if(pin == GPIO_Pin_3)
	{
		return GPIO_PinSource3;
	}
	else if(pin == GPIO_Pin_4)
	{
		return GPIO_PinSource4;
	}
	else if(pin == GPIO_Pin_5)
	{
		return GPIO_PinSource5;
	}
	else if(pin == GPIO_Pin_6)
	{
		return GPIO_PinSource6;
	}
	else if(pin == GPIO_Pin_7)
	{
		return GPIO_PinSource7;
	}
	else if(pin == GPIO_Pin_8)
	{
		return GPIO_PinSource8;
	}
	else if(pin == GPIO_Pin_9)
	{
		return GPIO_PinSource9;
	}
	else if(pin == GPIO_Pin_10)
	{
		return GPIO_PinSource10;
	}
	else if(pin == GPIO_Pin_11)
	{
		return GPIO_PinSource11;
	}
	else if(pin == GPIO_Pin_12)
	{
		return GPIO_PinSource12;
	}
	else if(pin == GPIO_Pin_13)
	{
		return GPIO_PinSource13;
	}
	else if(pin == GPIO_Pin_14)
	{
		return GPIO_PinSource14;
	}
	else if(pin == GPIO_Pin_15)
	{
		return GPIO_PinSource15;
	}
}

