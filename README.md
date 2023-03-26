# Modbus Ethernet Library for Arduino
Over TCP/IP implementation for Arduino Ethernet shield

[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/epsilonrt/modbus-ethernet?include_prereleases)](https://github.com/epsilonrt/modbus-ethernet/releases) 
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/epsilonrt/library/modbus-ethernet.svg)](https://registry.platformio.org/libraries/epsilonrt/modbus-ethernet) 
[![Arduino Registry](https://www.ardu-badge.com/badge/Modbus-Ethernet.svg)](https://www.arduinolibraries.info/libraries/modbus-ethernet)

[![Framework](https://img.shields.io/badge/Framework-Arduino-blue)](https://www.arduino.cc/)
[![Platform ATMELAVR](https://img.shields.io/badge/Platform-AtmelAVR-blue)](#)
[![Platform ATMELSAMD](https://img.shields.io/badge/Platform-AtmelSAMD-blue)](#)
[![Build](https://github.com/epsilonrt/modbus-ethernet/actions/workflows/build.yml/badge.svg)](https://github.com/epsilonrt/modbus-ethernet/actions/workflows/build.yml) 

---

This library allows your Arduino to communicate via Modbus protocol. The Modbus is a master-slave protocol
used in industrial automation and can be used in other areas, such as home automation.

The Modbus generally uses serial RS-232 or RS-485 as physical layer (then called Modbus Serial) and
TCP/IP via Ethernet or WiFi (Modbus TCP).

In the current version the library allows the Arduino operate **as a slave**, supporting Modbus over TCP.

## How to

There are four classes corresponding to five headers that may be used:

* [Modbus-Arduino](http://github.com/epsilonrt/modbus-arduino ) - Base Library
* [Modbus-Serial](https://github.com/epsilonrt/modbus-serial) - Modbus Serial RTU Library    
* [Modbus-Ethernet](https://github.com/epsilonrt/modbus-ethernet) - Modbus TCP Library (standard Ethernet Shield)   
* [Modbus-EtherCard](https://github.com/epsilonrt/modbus-ethercard) - Modbus TCP Library (for ENC28J60 chip)  
* [Modbus-Esp8266AT](https://github.com/epsilonrt/modbus-esp8266at) - Modbus IP Library (for ESP8266 chip with AT firmware)   

By opting for Modbus Serial or Modbus TCP you must include in your sketch the corresponding header and the base library header, eg:

    #include <Modbus.h>
    #include <ModbusSerial.h>

## Modbus-Ethernet

There are four examples that can be accessed from the Arduino interface, once you have installed the library.
Let's look at the example Switch.ino (only the parts concerning Modbus will be commented):

    #include <SPI.h>
    #include <Ethernet.h>
    #include <Modbus.h>
    #include <ModbusEthernet.h>

Inclusion of the necessary libraries.

    const int SWITCH_ISTS = 100;

Sets the Modbus register to represent the switch. This value is the offset (0-based) to be placed in its supervisory or testing software.
Note that if your software uses offsets 1-based the set value there should be 101, for this example.

    ModbusEthernet mb;

Create the mb instance (ModbusEthernet) to be used.

    mac byte [] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    ip byte [] = {192, 168, 1, 120};
    mb.config (mac, ip);

Sets the Ethernet shield. The values ​​of the MAC Address and the IP are passed by the config() method.
The syntax is equal to Arduino Ethernet class, and supports the following formats:

    void config (uint8_t * mac)
    void config (uint8_t * mac, IPAddress ip)
    void config (uint8_t * mac, IPAddress ip, IPAddress dns)
    void config (uint8_t * mac, IPAddress ip, IPAddress dns, gateway IPAddress)
    void config (uint8_t * mac, IPAddress ip, IPAddress dns, IPAddress gateway, subnet IPAddress)

Then we have:

    mb.addCoil (Lamp1Coil);

Adds the register type Coil (digital output) that will be responsible for 
activating the LED or lamp and verify their status. 
The library allows you to set an initial value for the register:

    mb.addCoil (Lamp1Coil, true);

In this case the register is added and set to true. If you use the first form 
the default value is false.

    mb.task ();

This method makes all magic, answering requests and changing the registers if 
necessary, it should be called only once, early in the loop.

    digitalWrite (LedPin, mb.coil (Lamp1Coil));

Finally the value of Lamp1Coil register is used to drive the lamp or LED.

In much the same way, the other examples show the use of other methods available in the library:

    void addCoil (offset word, bool value)
    void addHreg (offset word, word value)
    void addIsts (offset word, bool value)
    void addIreg (offset word, word value)

Adds registers and configures initial value if specified.

    bool setCoil (offset word, bool value)
    bool setHreg (offset word, word value)
    bool setIsts (offset word, bool value)
    bool setIReg (offset word, word value)

Sets a value to the register.

    bool coil (offset word)
    word hreg  (word offset)
    bool ists (offset word)
    word ireg (word offset)

Returns the value of a register.

**Notes:**

1. When using Modbus TCP the transport protocol is TCP (port 502) and, by default, 
the connection is terminated to each transmitted message, that is, is not a 
keep-alive type connection. If you need a TCP keep-alive connection you have to 
remove comments of this line in ModbusEthernet.h header (or ModbusEthercard.h ModbusEsp8266AT.h headers):

		#define TCP_KEEP_ALIVE

License
=======
The code in this repo is licensed under the BSD New License. See LICENSE for more info.

