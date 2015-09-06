//includes all of the standard peripheral libraries
#include "stm32f4xx_conf.h"

/* C++ libraries */
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




 void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

//initializes the leds used for debugging  
gpio green(GPIOD, GPIO_Pin_12);  
gpio orange(GPIOD, GPIO_Pin_13);
gpio red(GPIOD, GPIO_Pin_14);
gpio blue(GPIOD, GPIO_Pin_15);


int main(void)
{
	//you must first initialize the usart that you want to use
	serial five(GPIOD, GPIO_Pin_2, GPIOC, GPIO_Pin_12, UART5, 57600);
	
	//after the usart has been initialized, you can then initialize the usartDMA class
	usartDma DMAfive(UART5);
	
	//to activate the TX with DMA you must run this function on the instance you just created
	//look at usartDMA.h file to understand what each parameter is doing
	DMAfive.initTx(2, DMA1_Stream7, DMA_Channel_4);
	
	//inserts a value into the buffer that the dma will send out with tx
	DMAfive.insert(0, 0);
	DMAfive.insert(56, 1);
	

	while (1)
	{
		//this command sends the data
		DMAfive.send();

		green.toggle();
	  
		Delay(0xffffff);
    
	}
}






