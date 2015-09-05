#include "stm32f4xx_conf.h"

/* C++ libraries */
#include "led.h"
#include "gpio.h"
#include "servo.h"
#include "pwm.h"
#include "adc.h"
#include "serial.h"
#include "usartDma.h"

#define ARM_MATH_CM4  //tells the preprocessor this is a M4 model chip
#include "arm_math.h"  //cool math functions like transforms and PID controller

#include "interrupts.h"  //where the interrupt functions are located
#include "stm32f4xx_it.h"  //where non peripheral interrupt are located
#include <cstdarg>  //library to allow variable amount of argument inputs


uint8_t checksum(uint8_t* packet, uint8_t size) {
	uint8_t crc = 0;
	
	for (uint8_t i = 1; i < size + 1; i++) {
		uint8_t inbyte = packet[i];
		for (uint8_t i = 8; i; i--) {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix)
				crc ^= 0xD5;
			inbyte >>= 1;
		}
	}
	return crc;
}

 void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

gpio green(GPIOD, GPIO_Pin_10);  
gpio orange(GPIOD, GPIO_Pin_11);
gpio red(GPIOD, GPIO_Pin_12);
gpio blue(GPIOD, GPIO_Pin_13);


int main(void)
{
	serial four(GPIOD, GPIO_Pin_2, GPIOC, GPIO_Pin_12, UART5, 57600);
	
	uint8_t packet[8][7];
	
	for(int i = 0; i < 8; i++)
	{
		//Stores the correct values into the packets to be sent to the motors
		packet[i][1] = i + 1;
		packet[i][2] = 1;
		packet[i][3] = 1;
		packet[i][4] = 100;
		packet[i][5] = checksum(packet[i], 4);
		packet[i][6] = 0x13;
		packet[i][0] = 0x12;  //This is out of place because it gives me errors if I set the start byte value first
	}
	
	
	
	
  while (1)
  {
	for(int i = 0; i < 8; i++)
	{
		four.write(packet[i], 7);  
	}
	  
	  
	  
	Delay(0xfffff);

	green.on();  
	orange.on();
	red.on();
    
  }
}






