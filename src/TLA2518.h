/*
  This file is part of the IOExpander-TLA2518 library.
  Copyright (c) 2022 Good Solutions Sweden AB. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
	int readAnalogInput(uint8_t input, uint8_t* data);
private:
	SPIClass* _spi;
	int _csPin;
	SPISettings _spiSettings;
};

