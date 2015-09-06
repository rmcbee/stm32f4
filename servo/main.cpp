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

gpio green(GPIOD, GPIO_Pin_12);  
gpio orange(GPIOD, GPIO_Pin_13);
gpio red(GPIOD, GPIO_Pin_14);
gpio blue(GPIOD, GPIO_Pin_15);


int main(void)
{
	servo myServo(GPIOA, GPIO_Pin_0, TIM2 , 1);
	
	
	/*
	These are some other function that can be used with the servo class. They allow the user to change
	the max and min pulse length that the servo will receive and the max and min angle the servo can
	turn in. Each servo is different, so you'll be able to change these values to fit that servo.
	
	myServo.setMaxPulseLength(2.1);
	myServo.setMinPulseLength(0.9);
	myServo.setMaxAngle(180);
	myServo.setMinAngle(0);*/
	
	uint8_t angle = 0;  //variable used for angle
	
	
	
	while (1)
	  {
		for(int i = 0; i < 180; i++)
		{
			myServo.setAngle(i);
			Delay(0x1ffff);
		}
		  
		for(int i = 180; i > 0; i--)
		{
			myServo.setAngle(i);
			Delay(0x1ffff);
		}  
	    
	}
}






