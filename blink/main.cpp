#include "stm32f4xx_conf.h"  //includes the standard peripheral library

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


//a simple delay function
 void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

gpio green(GPIOD, GPIO_Pin_12);  //this initializes the green led with is located on bank D and is pin 12 on that bank



int main(void)
{
	
	

  while (1)
  {
	/*This chunk of code turns on the green led waits a little bit and then turns it off */

	  green.on();  //turn on green led
	  
	  Delay(0xffffff);
	  
	  green.off();  //turn off green led
	  
	  Delay(0xffffff);
	  
	  /*This chunk of code toggles the led state. Toggleing is just a fancy term meaning to switch it 	
	     to the oppisite state that it is not currently in. This chunk of code does the exact same thing
	     as the code above does. */
	  
	  green.toggle();  //toggles the green led on
	  
	  Delay(0xffffff);
	  
	  green.toggle();  //toggle the green led off
	  
	  Delay(0xffffff);
	  
  }
}






