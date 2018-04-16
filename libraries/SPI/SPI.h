/*
 * SPI Master library for Arduino Zero.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

#define SPI_MODE0 0x02
#define SPI_MODE1 0x00
#define SPI_MODE2 0x03
#define SPI_MODE3 0x01

#define MSB_FIRST 1
#define LSB_FIRST 0

enum {
	SPI_TRANSFER_SIZE_1_BYTES = 0,
	SPI_TRANSFER_SIZE_2_BYTES,
	SPI_TRANSFER_SIZE_4_BYTES,
};

class SPISettings {
  public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    if (__builtin_constant_p(clock)) {
      init_AlwaysInline(clock, bitOrder, dataMode);
    } else {
      init_MightInline(clock, bitOrder, dataMode);
    }
  }

  // Default speed set to 4MHz, SPI mode set to MODE 0 and Bit order set to MSB first.
  SPISettings() { init_AlwaysInline(4000000, MSB_FIRST, SPI_MODE0); }

  private:
  void init_MightInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }

  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
    this->clockFreq = clock;
    this->bitOrder = bitOrder;
    this->dataMode = dataMode;
  }

  uint32_t clockFreq;
  uint8_t dataMode;
  uint8_t bitOrder;

  friend class SPIClass;
};

class SPIClass {
  public:
  SPIClass(Spigroup *p_spi, uint8_t uc_pinMISO, uint8_t uc_pinSCK, uint8_t uc_pinMOSI, int8_t uc_pinSS = -1);


  byte transfer(uint8_t data);
  uint16_t transfer16(uint16_t data);
  void transfer(void *buf, size_t count);

  // Transaction Functions
  void usingInterrupt(int interruptNumber);
  void beginTransaction(SPISettings settings);
  void endTransaction(void);

  // SPI Configuration methods
  void attachInterrupt();
  void detachInterrupt();

  void begin();
  void end();

  void setBitOrder(uint8_t order);
  void setDataMode(uint8_t uc_mode);
  void setClockDivider(uint8_t uc_div);

  private:
  void init();
  void config(SPISettings settings);

  Spigroup *_hw;
  uint8_t _uc_pinMiso;
  uint8_t _uc_pinMosi;
  uint8_t _uc_pinSCK;
  int8_t _uc_pinSS;

  bool initialized;
  uint8_t interruptMode;
  char interruptSave;
  uint32_t interruptMask;

  uint32_t savedImask;
};

#if SPI_INTERFACES_COUNT > 0
  extern SPIClass SPI;
#endif
#if SPI_INTERFACES_COUNT > 1
  extern SPIClass _SPI1;
#endif
#if SPI_INTERFACES_COUNT > 2
  extern SPIClass _SPI2;
#endif
#if SPI_INTERFACES_COUNT > 3
  extern SPIClass _SPI3;
#endif
#if SPI_INTERFACES_COUNT > 4
  extern SPIClass _SPI4;
#endif
#if SPI_INTERFACES_COUNT > 5
  extern SPIClass _SPI5;
#endif

#endif
