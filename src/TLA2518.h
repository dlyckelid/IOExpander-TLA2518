/*
 Name:    TLA2518.h
 Created: 11/28/2022 8:55:21 AM
 Author:  David
 Editor:  http://www.visualmicro.com
*/

#pragma once
#include <Arduino.h>
#include <SPI.h>
#include "tla2528.h"


class TLA2518Class {
public:
	TLA2518Class(SPIClass& spi, int csPin);
	virtual ~TLA2518Class();

	int begin();
	void end();
	void readStatus();
	int readAnalogInput(uint8_t input, uint8_t* data);
	void digitalWrite(uint8_t pin, uint8_t val);
	uint8_t digitalRead(uint8_t pin);
	int analogRead(uint8_t pin);
	void pinMode(uint8_t pin, uint8_t mode);

private:
	int readRegister(uint8_t address);
	int readRegisters(uint8_t address, uint8_t* data, size_t length);
	int writeRegister(uint8_t address, uint8_t value);
	int setBit(uint8_t address, uint8_t bit);
	int resetBit(uint8_t address, uint8_t bit);
private:
	SPIClass* _spi;
	int _csPin;
	SPISettings _spiSettings;
};

