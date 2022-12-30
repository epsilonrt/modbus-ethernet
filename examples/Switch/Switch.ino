/**
  @file Switch.ino
  Modbus-Arduino Example - Switch (Modbus TCP using Ethernet shield)
  Copyright by André Sarmento Barbosa
  https://github.com/epsilonrt/modbus-ethernet
*/
 
#include <ModbusEthernet.h>

//Modbus Registers Offsets (0-9999)
const int SWITCH_ISTS = 100; 
//Used Pins
const int switchPin = 3;

//ModbusEthernet object
ModbusEthernet mb;

void setup() {
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
    // The IP address for the shield
    byte ip[] = { 192, 168, 1, 120 };   
    // Config Modbus TCP 
    mb.config(mac, ip);
    //Set ledPin mode
    pinMode(switchPin, INPUT);
    // Add SWITCH_ISTS register - Use addIsts() for digital inputs 
    mb.addIsts(SWITCH_ISTS);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   
   //Attach switchPin to SWITCH_ISTS register     
   mb.Ists(SWITCH_ISTS, digitalRead(switchPin));
}
