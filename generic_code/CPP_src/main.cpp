

#include "stm32f4xx_conf.h"  //includes all of the peripheral .h files needed for stm32f4

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



 void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	} 
}

//initializes the leds
gpio green(GPIOD, GPIO_Pin_12);  
gpio orange(GPIOD, GPIO_Pin_13);
gpio red(GPIOD, GPIO_Pin_14);
gpio blue(GPIOD, GPIO_Pin_15);



int main(void)
{
	

	

  while (1)
  {
    
  }
}



