# stm32f4

This setup is based on the STM32F4xx_StdPeriph_Driver as well as the excellent Linux port of STLink by [Texane](https://github.com/texane/stlink) 

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

Things to do

#### Main board




