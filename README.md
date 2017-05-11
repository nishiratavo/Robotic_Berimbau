# Robotic Berimbau

This project is an attempt to develop a fully automated system that plays the Berimbau through the MIDI protocol. The hardware we are using is the Arduino UNO platform with a custom built shield.

## Build Dependencies
   * avr-gcc (>= 4.9)
   * avrdude
   * make

## Installing the AVR GCC Tool Chain

### GNU/Linux

#### Ubuntu (16.04)

```
$ sudo apt install make avr-libc avrdude binutils-avr gcc-avr
```

#### Arch Linux

```
$ sudo pacman -S avr-gcc avr-binutils make avr-libc avrdude
```

Remember to give the current user permissions to access serial ports (on Ubuntu and derivatives you need to include the user in the **dialout** group, on Arch Linux the group is called **uucp**). Don't forget to logout and login to update the user permissions.

### MacOS
The required dependencies can be installed through the [homebrew](https://brew.sh/) package manager.

```
$ brew tap osx-cross/avr
$ brew install avr-libc avr-gcc avr-binutils avrdude
```

### Windows
Download the complete [AVR Tool Chain compiled for Windows](https://www.dropbox.com/s/cqqs4lxoz5l7v3g/avr8-gnu-toolchain.zip?dl=0). Extract the compressed file into "C:\Program Files\". Add the "C:\Program Files\avr8-gnu-toolchain\bin\" directory to the [PATH environment variable](https://www.computerhope.com/issues/ch000549.htm).

## How to build and upload
Open a terminal and navigate to the cloned repository directory. Then execute the ```make``` command to compile the source code. To upload you need to issue the "make burn PGPORT=xxx" where 'xxx' is the serial port name where the Arduino UNO is connected (on Linux it's typically /dev/ttyACMx or /dev/ttyUSBx, on macOS it will have different names depending on the USB to Serial bridge used, but is typically /dev/tty.usbmodemxxxx, on Windows it will be a COMx, where 'x' varies from 1 to 9).
