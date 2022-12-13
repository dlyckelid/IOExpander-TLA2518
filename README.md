# IOExpander-TLA2518

Simple library to set basic settings and usage of a TLA-2518 IOExpander
https://www.ti.com/product/TLA2518

# Usage
## Constructor
```
TLA2518Class(SPIClass& spi, int csPin);
```
## Functions
### int begin()
Starts communication with TLA2518 and returns 1 if succeded
### void end()
Ends communication
### void readStatus()
Prints current status from device to Serial
### void digitalWrite(uint8_t pin, uint8_t val);
Sets output to "val" on output enabled pin (0-7)
### uint8_t digitalRead(uint8_t pin);
Reads digital value of input enabled pin (0-7)
### int analogRead(uint8_t pin);
Returns analog value from Analog enabled input
###  pinMode(uint8_t pin, uint8_t mode);
Sets pin mode on pin (0-7)
```
#include "TLA2518.h"


TLA2518Class ioexpander = TLA2518Class(vspi,5);
if(ioexpander.begin())
{
  #Assign pins
  ioexpander.pinModeIO(0,OUTPUT);
  ioexpander.pinModeIO(1,INPUT);
  ioexpander.pinModeIO(2,ANALOG);
  ioexpander.pinModeIO(3,ANALOG);
  ioexpander.pinModeIO(4,ANALOG);
  ioexpander.pinModeIO(5,INPUT);
  ioexpander.pinModeIO(6,OUTPUT);
  ioexpander.pinModeIO(7,OUTPUT);
  
  #Set outputs
  ioexpander.digitalWriteIO(0,LOW);
  ioexpander.digitalWriteIO(6,HIGH);
  ioexpander.digitalWriteIO(7,LOW);
  
  #Read inputs
  uint8_t valPin1 = ioexpander.digitalReadIO(1);
  uint8_t valPin5 = ioexpander.digitalReadIO(5);
  
  #Read analog inputs
  int valAnalog2 = ioexpander.analogReadIO(2);
  int valAnalog3 = ioexpander.analogReadIO(3);
  int valAnalog4 = ioexpander.analogReadIO(4);
}

ioexpander.end();
```
