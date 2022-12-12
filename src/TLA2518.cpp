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

#include "TLA2518.h"



TLA2518Class::TLA2518Class(SPIClass& spi, int csPin) :
    _spi(&spi),
    _csPin(csPin),
    _spiSettings(10E6, MSBFIRST, SPI_MODE0)
{
}

TLA2518Class::~TLA2518Class()
{
}

int TLA2518Class::begin()
{
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    _spi->begin();
    if (readRegister(SYSTEM_STATUS_ADDRESS))
    {
        ////writeRegister(GENERAL_CFG_ADDRESS,0b00000001);
        //writeRegister(PIN_CFG_ADDRESS, 0b11100011);
        //writeRegister(GPIO_CFG_ADDRESS, 0b11100011);
        //writeRegister(GPO_DRIVE_CFG_ADDRESS, 0b11100011);
        //writeRegister(GPO_VALUE_ADDRESS, 0b00000000);

        ////setBit(DATA_CFG_ADDRESS,0b00010000);

        readStatus();

        return 1;
    }
    return 0;
}

void TLA2518Class::end()
{
    _spi->end();
    digitalWrite(_csPin, LOW);
    pinMode(_csPin, INPUT);
}

void TLA2518Class::readStatus()
{
    Serial.println("-------- TLA2518 --------");
    Serial.println(readRegister(SYSTEM_STATUS_ADDRESS));
    Serial.println(readRegister(GENERAL_CFG_ADDRESS));
    Serial.println(readRegister(DATA_CFG_ADDRESS));
    Serial.println(readRegister(OSR_CFG_ADDRESS));
    Serial.println(readRegister(OPMODE_CFG_ADDRESS));
    Serial.println(readRegister(PIN_CFG_ADDRESS));
    Serial.println(readRegister(GPIO_CFG_ADDRESS));
    Serial.println(readRegister(GPO_DRIVE_CFG_ADDRESS));
    Serial.println(readRegister(GPO_VALUE_ADDRESS));
    Serial.println(readRegister(GPI_VALUE_ADDRESS));
    Serial.println(readRegister(SEQUENCE_CFG_ADDRESS));
    Serial.println(readRegister(MANUAL_CH_SEL_ADDRESS));

    Serial.println("-------- TLA2518 --------");
}

int TLA2518Class::readRegister(uint8_t address)
{
    uint8_t value;

    if (readRegisters(address, &value, sizeof(value)) != 1) {
        return -1;
    }

    return value;
}

int TLA2518Class::readRegisters(uint8_t address, uint8_t* data, size_t length)
{
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0b00010000);
    _spi->transfer(address);
    _spi->transfer(0b00000000);
    digitalWrite(_csPin, HIGH);
    digitalWrite(_csPin, LOW);
    _spi->transfer(data, length);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();

    return 1;
}

int TLA2518Class::readAnalogInput(uint8_t input, uint8_t* data)
{
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0b00001000);
    _spi->transfer(MANUAL_CH_SEL_ADDRESS);
    _spi->transfer(input);
    digitalWrite(_csPin, HIGH);
    digitalWrite(_csPin, LOW);
    _spi->transfer(data, sizeof(data));
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();

    return 1;
}

void TLA2518Class::digitalWrite(uint8_t pin, uint8_t val)
{
    if (pin >= 0 && pin <= 7)
    {
        if (val)
        {
            setBit(GPO_VALUE_ADDRESS, 1 << pin);
        }
        else
        {
            resetBit(GPO_VALUE_ADDRESS, 1 << pin);
        }
    }
}

uint8_t TLA2518Class::digitalRead(uint8_t pin)
{
    if (pin >= 0 && pin < 8)
    {
        int result = readRegister(GPI_VALUE_ADDRESS);

        return (result >> pin) & 0x1;
    }
    return uint8_t();
}

int TLA2518Class::analogRead(uint8_t pin)
{
    uint8_t value[3];
    readAnalogInput(pin, (uint8_t*)value);
    return (value[0] << 4) | (value[1] >> 4);
}

void TLA2518Class::pinMode(uint8_t pin, uint8_t mode)
{
    if (pin < 8)
    {
        switch (mode)
        {
        case INPUT:
            setBit(PIN_CFG_ADDRESS, 1 << pin);
            resetBit(GPIO_CFG_ADDRESS, 1 << pin);
            break;
        case OUTPUT:
            setBit(PIN_CFG_ADDRESS, 1 << pin);
            setBit(GPIO_CFG_ADDRESS, 1 << pin);
            setBit(GPO_DRIVE_CFG_ADDRESS, 1 << pin);
            break;
        case ANALOG:
            resetBit(PIN_CFG_ADDRESS, 1 << pin);
            resetBit(GPIO_CFG_ADDRESS, 1 << pin);
            break;
        }
    }
}

int TLA2518Class::writeRegister(uint8_t address, uint8_t value)
{
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0b00010000);
    _spi->transfer(address);
    _spi->transfer(value);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();


    return 1;
}

int TLA2518Class::setBit(uint8_t address, uint8_t value)
{
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0b00011000);
    _spi->transfer(address);
    _spi->transfer(value);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();


    return 1;
}

int TLA2518Class::resetBit(uint8_t address, uint8_t value)
{
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0b00100000);
    _spi->transfer(address);
    _spi->transfer(value);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();


    return 1;
}
