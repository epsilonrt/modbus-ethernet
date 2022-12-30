# Modbus Library for Arduino - Over TCP/IP implementation for Arduino Ethernet shield

[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/epsilonrt/modbus-ethernet?include_prereleases)](https://github.com/epsilonrt/modbus-ethernet/releases) 
[![Framework](https://img.shields.io/badge/Framework-Arduino-blue)](https://www.arduino.cc/)
[![Build](https://github.com/epsilonrt/modbus-ethernet/actions/workflows/build.yml/badge.svg)](https://github.com/epsilonrt/modbus-ethernet/actions/workflows/build.yml) 

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/epsilonrt/library/modbus-ethernet.svg)](https://registry.platformio.org/libraries/epsilonrt/modbus-ethernet) 
[![Platform ATMELAVR](https://img.shields.io/badge/Platform-AtmelAVR-blue)](#)
[![Platform ATMELSAMD](https://img.shields.io/badge/Platform-AtmelSAMD-blue)](#)

---

This library allows your Arduino to communicate via Modbus protocol. The Modbus is a master-slave protocol
used in industrial automation and can be used in other areas, such as home automation.

The Modbus generally uses serial RS-232 or RS-485 as physical layer (then called Modbus Serial) and
TCP/IP via Ethernet or WiFi (Modbus TCP).

In the current version the library allows the Arduino operate **as a slave**, supporting Modbus over TCP.

## How to

There are four classes corresponding to five headers that may be used:

* [Modbus](http://github.com/epsilonrt/modbus-arduino ) - Base Library
* [ModbusSerial](https://github.com/epsilonrt/modbus-serial) - Modbus Serial RTU Library    
* [ModbusEthernet](https://github.com/epsilonrt/modbus-ethernet) - Modbus TCP Library (standard Ethernet Shield)   
* [ModbusEthercard](https://github.com/epsilonrt/modbus-ethercard) - Modbus TCP Library (for ENC28J60 chip)  
* [ModbusEsp8266AT](https://github.com/epsilonrt/modbus-esp8266at) - Modbus IP Library (for ESP8266 chip with AT firmware)   

By opting for Modbus Serial or Modbus TCP you must include in your sketch the corresponding header and the base library header, eg:

    #include <Modbus.h>
    #include <ModbusSerial.h>

## ModbusEthernet

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

    mb.addIsts (SWITCH_ISTS);

Adds the register type Input Status (digital input) that is responsible for detecting if a switch is in state on or off.
The library allows you to set an initial value for the register:

    mb.addIsts (SWITCH_ISTS, true);

In this case the register is added and set to true. If you use the first form the default value is false.

    mb.task ();

This method makes all magic, answering requests and changing the registers if necessary, it should be called only once, early in the loop.

    mb.Ists (SWITCH_ISTS, digitalRead (switchPin));

Finally the value of SWITCH_ISTS register changes as the state of the selected digital input.

**Notes:**

1. When using Modbus TCP the transport protocol is TCP (port 502) and, by default, 
the connection is terminated to each transmitted message, that is, is not a 
keep-alive type connection. If you need a TCP keep-alive connection you have to 
remove comments of this line in ModbusEthernet.h header (or ModbusEthercard.h ModbusEsp8266AT.h headers):

		#define TCP_KEEP_ALIVE

Contributions
=============
http://github.com/epsilonrt/modbus-arduino  
epsilonrt (at) gmail (dot) com  
prof (at) andresarmento (dot) com  

License
=======
The code in this repo is licensed under the BSD New License. See LICENSE for more info.

