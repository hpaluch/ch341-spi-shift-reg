# SPI example for CH341 USB adapter 

Here is working SPI example for CH341 USB adapter.
This example uses 2x D flip-flop to make 2-bit shift register (2-bit "delay" on
output)


Circuit schematic is below:

![Schematic of example SPI circuit](https://github.com/hpaluch/ch341-spi-shift-reg/blob/master/ExpressPCB/ch341-spi-shiftreg.png?raw=true)


# Requirements

Hardware:
* you
  need [CH341A USB to UART/IIC/SPI/TTL/ISP adapter EPP/MEM Parallel converter]
  I got my from Amazon.de as [DollaTek CH341A USB zu UART/IIC/SPI/TTL/ISP Adapter EPP/MEM Parallelwandler]. If you never used this module
  please see my article [Getting started with LC CH341A USB conversion module]
* parts required to create above Sample Circuit - see schematics

Software:

* Windows OS - I tested this project on Windows XP SP3 guest in VirtualBox
* Visual Studio 2010 (This it the last version supported on XP SP3)


# Setup

The CH341A adapter must be setup following way:
* jumper set to `I2C/SPI` mode
* voltage set to 5V TTL logic (this is because used CD4013 D Flip-Flop
  would be near by required minimum voltage in case of 3.3V and too slow)
* please see picture below for correct configuration:

![USB CH341A adapter configuration](https://github.com/hpaluch/ch341-spi-shift-reg/blob/master/images/ch341-spi-5v.jpg?raw=true)


Software setup:
*  Download and install [CH341PAR.ZIP] - USB driver for CH341 chip
   in Parallel mode (EPP, MEM). This driver is valid 
   also for **I2C mode and SPI mode** (yes - even when it is marked parallel).
*  install VisualSutdio 2010

Create environment variable `CH341_SDK` that should point to extracted
`CH341PAR.ZIP` header and library files. For example
if you have extracted file:

```
C:\CH341_DRIVER\LIB\C\CH341DLL.H 
```
Then your `CH341_SDK` should be set to `C:\CH341_DRIVER\LIB\C`.

Open and rebuild solution `TestSPI_VS2010/ch341_spi_shiftreg.sln`
in VisualStudio 2010. There should be no errors.

Connect your `CH341A USB module` to target circuit. Following pins are used:

|PIN Name|Direction|Description|
|--------|---------|-----------|
|GND|N/A|Common ground|
|VCC|N/A|5V supply|
|MISO|Input|master in slave out - SPI|
|MOSI|Output|master out slave in - SPI|
|SCK|Output|master clock - SPI|
|/CS0|Output|Chip select 0, active in Low <sup>1</sup>|

----
1) The `/CS0` signal is currently used by Logic Analyzer only
   (not connected to test circuit)

NOTE: Direction is from `CH341A USB Module` "view".

Connect your `CH341 USB module` to your PC. There should
be permanently lighting red LED on USB module.

When you run example program you should see output like:
```
CH341 SPI shift register example
CH341 version: 33
Device 0 name is '\\?\usb#vid_1a86&pid_5512#5&18f54cb7&0&1#{5446f048-98b4-4ef0-9
6e8-27994bac0d00}'
Opening device# 0
Sending to SPI:
Index=0, Value=0xaa
Index=1, Value=0x55
SPI returned back data:
Index=0, Value=0x6a
Index=1, Value=0x95
```
And LED D1 should be ON.

NOTES: 1st and 2nd bits of returned data can be different than as shown in
above listings - because these are values from two previous clock ticks
(or should `0` after CD4013 reset)

# Output

Here is output from PulseView:

![SPI communication - PulseView](https://github.com/hpaluch/ch341-spi-shift-reg/blob/master/PulseView/pulseview-ch341-spi-shiftreg.png?raw=true)

Please see yellow arrows - how the data are exactly shifted
by 2 bits - thanks to these 2 D Flip-Flops working as 2-bit shift register.

And here is also `/CS0` signal (not used in this circuit) - only
start shown (I used `while(1){ CH341StreamSPI4(); Sleep(10);}` loop to generate
data for Logic Analyzer):

![/CS0 start - PulseView](https://github.com/hpaluch/ch341-spi-shift-reg/blob/master/PulseView/pulseview-ch341-spi-shiftreg-cs-start.png?raw=true)

[CH341PAR.ZIP]: http://www.wch.cn/downloads/file/7.html
[Getting started with LC CH341A USB conversion module]:  https://github.com/hpaluch/hpaluch.github.io/wiki/Getting-started-with-LC-CH341A-USB-conversion-module
[CH341A USB to UART/IIC/SPI/TTL/ISP adapter EPP/MEM Parallel converter]:http://www.chinalctech.com/index.php?_m=mod_product&_a=view&p_id=1220
[DollaTek CH341A USB zu UART/IIC/SPI/TTL/ISP Adapter EPP/MEM Parallelwandler]:https://www.amazon.de/gp/product/B07DJZDRKG/
