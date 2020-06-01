# Openmote-CC2538-Sensor-Nodes Setup in Ubutnu

Please follow these instructions in order to start development with OpenMote nodes:
The instructions are mainly copied from following links:
http://www.openmote.com/blog/bootstrapping-the-openmote-platform.html
http://www.openmote.com/blog/getting-started-with-contiki-and-openmote.html
https://github.com/contiki-os/contiki/tree/master/platform/openmote-cc2538
1. Install Ubutnu 14.04 on your system. (This tutorial has been tested on this version).
2. Install the toolchain for C/C++ compiler for ARM Cortex platform using following command:
sudo add-apt-repository -y ppa:terry.guo/gcc-arm-embedded sudo apt-get update
sudo apt-get dist-upgrade sudo apt-get install build-essential gcc-arm-none-eabi
libnewlib-arm-none-eabi
3. You also need to install C/C++ standard library for ARM MCU using following command:
wget http://mirrors.kernel.org/ubuntu/pool/universe/libs/libstdc++-arm-noneeabi/libstdc++-arm-none-eabi-newlib_4.8.3-11ubuntu1+4_all.deb sudo dpkg -i
libstdc++-arm-none-eabi-newlib_4.8.3-11ubuntu1+4_all.deb
4. Install Python to download the hex (binary) file to the microcontroller using serial flash tool.
5. Install Python serial module
6. Get the OpenMote firmare from github:
git clone --recursive https://github.com/OpenMote/firmware.git OpenMote/firmware
7. Once you have installed all required tools go to the projects folder:
cd OpenMote/firmware/projects
8. Run the following command to download the binary file to MCU:
make BOARD = OpenMote-cc2538 TARGET=cc2538 bsl
9. If there is an error that serial port is not available then do the following:
Make sure the openmote base board is connected to system.
Add user to the dialout group using following command
Sudo password –add [username] dialout
(logout and then login and error shall disapper)
These are the steps to download OpenMote firmware using the serial tool to MCU. If you want to use
the J Link tool then after you also need to follow these steps:
1. Download the j link debugger
2. Start Segger GDB server by issuing the following command
/home/[dir]/jlink-6.0.7.x86_64/opt/SEGGER/JLink_V60g/JLinkGDBServer -device
CC2538SF53
3. Once the Segger JLinkGDBServer is connected to the target device you need to go back to the
other terminal and issue the following command:
arm-none-eabi-gdb
After issuing this command you should see a window like the following. Here GDB is waiting for
you to input the commands to load the target code and start debugging.

4. Once GDB is executing, issue the following commands one by one in the GDB window:
target remote localhost:2331
monitor interface jtag
monitor speed 5000
monitor endian little
monitor flash download = 1
monitor flash breakpoints = 1
monitor reset
load hello-world.elf
This commands are responsible for configuring the GDB client to talk to the GDB server (the one
executing in the other terminal) and loading the "Hello World" machine code compiled for the
CC2538 (located in the hello-world.elf file) to the OpenMote. At this point you should see the
code loading to the OpenMote, as depicted next.
