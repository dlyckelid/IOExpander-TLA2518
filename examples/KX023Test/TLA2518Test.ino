/*
  TLA2518 - IOExpander with 8 configurable I/O

  This example sets I/O of TLA2518 and then reads status of analog and digital inputs
  and continuously prints them to the Serial Monitor
  or Serial Plotter.

  created 12 Dec 2022
  by David Lyckelid

  This example code is in the public domain.
*/

#include <SPI.h>
#include <TLA2518.h>

SPIClass vspi(VSPI);

TLA2518Class *ioexpander;

void setup() {
  Serial.begin(9600);
  ioexpander = new TLA2518Class(vspi,5);
  if(ioexpander.begin())
  {
      //Assign pins
      ioexpander.pinMode(0,OUTPUT);
      ioexpander.pinMode(1,INPUT);
      ioexpander.pinMode(2,ANALOG);
      ioexpander.pinMode(3,ANALOG);
      ioexpander.pinMode(4,ANALOG);
      ioexpander.pinMode(5,INPUT);
      ioexpander.pinMode(6,OUTPUT);
      ioexpander.pinMode(7,OUTPUT);
      
      //Set outputs
      ioexpander.digitalWrite(0,LOW);
      ioexpander.digitalWrite(6,HIGH);
      ioexpander.digitalWrite(7,LOW);
      
  }
}


void loop()
{
  delay(1000);

  //Read inputs
  uint8_t valPin1 = digitalRead(1);
  uint8_t valPin5 = digitalRead(5);
  
  //Read analog inputs
  int valAnalog2 = analogRead(2);
  int valAnalog3 = analogRead(3);
  int valAnalog4 = analogRead(4);

  Serial.print(valPin1);
  Serial.print('\t');
  Serial.print(valPin2);
  Serial.print('\t');
  Serial.print(valAnalog2);
  Serial.print('\t');
  Serial.print(valAnalog3);
  Serial.print('\t');
  Serial.println(valAnalog4);
}
