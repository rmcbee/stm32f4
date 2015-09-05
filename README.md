# stm32f4

This respository contains a library for initializing and using the different peripherals offered by the stm32f4 family of microcontrollers.  

# Latest update 

## What are we using
This respository contains a library for initializing and using the different peripherals offered by the stm32f4 family of microcontrollers. 
This readme also contains instructions on how to set up your computer to be able to program these chips.

## How to get setup on Linux or Mac: 
1. Download GCC-ARM for your system from here https://launchpad.net/gcc-arm-embedded/+download 
2. Setup the path on your computer to the location of the downloaded GCC-ARM
3. Clone this directory to your computer
4. Clone the STLink program from the link above into a directory of your choosing
5. Follow the instructions on the STLink github to compile the program 
6. Add the STLink directory to your path
7. cd into IOToggle
8. run "make"
9. Plug in your discovery board via the mini-usb connector and run "make burn"
10. Voila! Your Discovery board will now be running the simple IOToggle program.

## How to get setup on Windows: 
1. Download GCC-ARM for your system from here [here](https://launchpad.net/gcc-arm-embedded/+download)
2. Setup the path on your computer to the location of the downloaded GCC-ARM
4. Download the Make Binaries for your computer from [here](http://gnuwin32.sourceforge.net/packages/make.htm)
5. Setup the path on your computer to the location of the download Make binaries. (Note you can also put these in the same directory as GCC-ARM)
6. Download the STLink program binaries from [here](http://www.emb4fun.de/archive/stlink/index.html)
7. Do the same as step 5 except for the STLink binaries.
8. Clone this directory to your computer
9. cd into IOToggle and run "make"
10. Plug in your discovery board via the mini-usb connector and run "make burn"
11. Viola! Your Discovery board will now be running the simple IOToggle program.

## Git How To
Please see the GitCommands.markdown file for basics on how to use git for this project.


### Tasks for embeded programming team 



### Who has our STM32F4 nucleo boards



#### Still useful but outdatd links

How to setup envirns

Windows with GCC and openOCD (not IAR) : http://www.angstromsandalgorithms.com/free-eclipse-arm-gcc-openocd-toolchain-for-windows-part-2-arm-gcc/

Linux: http://eliaselectronics.com/stm32f4-tutorials/setting-up-the-stm32f4-arm-development-toolchain/

and OSX : http://spin.atomicobject.com/2013/08/10/arm-cortex-m-toolchain/


Things to do

#### Main board




