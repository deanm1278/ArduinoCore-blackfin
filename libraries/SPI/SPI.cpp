/*
 * SPI Master library for DSP feather
 * Copyright (c) 2018 Dean Miller
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

#include "SPI.h"
#include <Arduino.h>
#include <wiring_private.h>

#define SPI_IMODE_NONE   0
#define SPI_IMODE_EXTINT 1
#define SPI_IMODE_GLOBAL 2

const SPISettings DEFAULT_SPI_SETTINGS = SPISettings();

SPIClass::SPIClass(Spigroup *p_spi, uint8_t uc_pinMISO, uint8_t uc_pinSCK, uint8_t uc_pinMOSI, int8_t uc_pinSS)
{
  initialized = false;
  _hw = p_spi;

  // pins
  _uc_pinMiso = uc_pinMISO;
  _uc_pinSCK = uc_pinSCK;
  _uc_pinMosi = uc_pinMOSI;
  _uc_pinSS = uc_pinSS;
}

void SPIClass::begin()
{
  init();

  // PIO init
  pinPeripheral(_uc_pinMiso, g_APinDescription[_uc_pinMiso].ulPinType);
  pinPeripheral(_uc_pinSCK, g_APinDescription[_uc_pinSCK].ulPinType);
  pinPeripheral(_uc_pinMosi, g_APinDescription[_uc_pinMosi].ulPinType);
  if(_uc_pinSS > -1)
      pinPeripheral(_uc_pinSS, g_APinDescription[_uc_pinSS].ulPinType);

  config(DEFAULT_SPI_SETTINGS);
}

void SPIClass::init()
{
  if (initialized)
    return;
  interruptMode = SPI_IMODE_NONE;
  interruptSave = 0;
  interruptMask = 0;
  initialized = true;
}

void SPIClass::config(SPISettings settings)
{
    if(_uc_pinSS > -1){
        //TODO: make this smarter
        switch(_uc_pinSS){
        case PIN_SPI_SS:
            _hw->SLVSEL.reg = (0xFF << 8) | (1 << 1);
        }
    }

    _hw->TXCTL.bit.TTI = 1;

    //set clocks BAUD = (SCLK0 / SPI Clock) - 1
    _hw->CLK.reg = (VARIANT_SCLK0 / settings.clockFreq) - 1;

    _hw->CTL.reg = ((_uc_pinSS > -1) << 6);

    setDataMode(settings.dataMode);
    setBitOrder(settings.bitOrder);

    _hw->CTL.reg |= 0x02;
}

void SPIClass::end()
{
  //TODO: deinit SPI periph
  initialized = false;
}

#ifndef interruptsStatus
#define interruptsStatus() __interruptsStatus()
static inline unsigned char __interruptsStatus(void) __attribute__((always_inline, unused));
static inline unsigned char __interruptsStatus(void)
{
#if 0 //TODO: this
  return (__get_PRIMASK() ? 0 : 1);
#else
  return 0;
#endif
}
#endif

void SPIClass::usingInterrupt(int interruptNumber)
{
  if ((interruptNumber == NOT_AN_INTERRUPT) || (interruptNumber == EXTERNAL_INT_NMI))
    return;

  uint8_t irestore = interruptsStatus();
  savedImask = noInterrupts();

  if (interruptNumber >= EXTERNAL_NUM_INTERRUPTS)
    interruptMode = SPI_IMODE_GLOBAL;
  else
  {
    interruptMode |= SPI_IMODE_EXTINT;
    interruptMask |= (1 << interruptNumber);
  }

  if (irestore)
    interrupts(savedImask);
}

void SPIClass::beginTransaction(SPISettings settings)
{
  if (interruptMode != SPI_IMODE_NONE)
  {
    if (interruptMode & SPI_IMODE_GLOBAL)
    {
      interruptSave = interruptsStatus();
      savedImask = noInterrupts();
    }
#if 0 //TODO: this
    else if (interruptMode & SPI_IMODE_EXTINT)
      EIC->INTENCLR.reg = EIC_INTENCLR_EXTINT(interruptMask);
#endif
  }

  config(settings);
}

void SPIClass::endTransaction(void)
{
  if (interruptMode != SPI_IMODE_NONE)
  {
    if (interruptMode & SPI_IMODE_GLOBAL)
    {
      if (interruptSave)
        interrupts(savedImask);
    }
#if 0 //TODO: this
    else if (interruptMode & SPI_IMODE_EXTINT)
      EIC->INTENSET.reg = EIC_INTENSET_EXTINT(interruptMask);
#endif
  }
}

void SPIClass::setBitOrder(uint8_t order)
{
  _hw->CTL.bit.LSBF = !order;
}

void SPIClass::setDataMode(uint8_t mode)
{
  switch (mode)
  {
    case SPI_MODE0:
        _hw->CTL.bit.CPOL = 0;
        _hw->CTL.bit.CPHA = 0;
        break;

    case SPI_MODE1:
        _hw->CTL.bit.CPOL = 1;
        _hw->CTL.bit.CPHA = 0;
        break;

    case SPI_MODE2:
        _hw->CTL.bit.CPOL = 0;
        _hw->CTL.bit.CPHA = 1;
        break;

    case SPI_MODE3:
        _hw->CTL.bit.CPOL = 1;
        _hw->CTL.bit.CPHA = 1;
        break;

    default:
      break;
  }
}

byte SPIClass::transfer(uint8_t data)
{
    _hw->TFIFO.reg = data;
    _hw->RXCTL.bit.REN = 1;
    _hw->TXCTL.bit.TEN = 1;
    _hw->CTL.reg |= 0x01;

    //wait for the byte to be ready in the FIFO
    while(_hw->STAT.bit.RFE);

    uint32_t readData = _hw->RFIFO.reg;
    return readData;
}

uint16_t SPIClass::transfer16(uint16_t data) {

	uint16_t low, high;

	high = transfer(data >> 8);
	low = transfer(data & 0xFF);

	return (high << 8) | (low & 0xFF);
}

void SPIClass::transfer(void *buf, size_t count)
{
  uint8_t *buffer = reinterpret_cast<uint8_t *>(buf);

  for(int i=0; i<count; i++){
	  *buffer = transfer(*buffer);
	  buffer++;
  }
}

void SPIClass::attachInterrupt() {
  // Should be enableInterrupt()
}

void SPIClass::detachInterrupt() {
  // Should be disableInterrupt()
}

#if SPI_INTERFACES_COUNT > 0
  /* In case new variant doesn't define these macros,
   * we put here the ones for dsp feather
   *
   * These values should be different on some variants!
   */
  #ifndef PERIPH_SPI
    #define PERIPH_SPI           SPI2
  #endif // PERIPH_SPI
  SPIClass SPI (PERIPH_SPI,  PIN_SPI_MISO,  PIN_SPI_SCK,  PIN_SPI_MOSI);
#endif
#if SPI_INTERFACES_COUNT > 1
  SPIClass _SPI1(PERIPH_SPI1, PIN_SPI1_MISO, PIN_SPI1_SCK, PIN_SPI1_MOSI);
#endif
#if SPI_INTERFACES_COUNT > 2
  SPIClass _SPI2(PERIPH_SPI2, PIN_SPI2_MISO, PIN_SPI2_SCK, PIN_SPI2_MOSI);
#endif
#if SPI_INTERFACES_COUNT > 3
  SPIClass _SPI3(PERIPH_SPI3, PIN_SPI3_MISO, PIN_SPI3_SCK, PIN_SPI3_MOSI);
#endif
#if SPI_INTERFACES_COUNT > 4
  SPIClass _SPI4(PERIPH_SPI4, PIN_SPI4_MISO, PIN_SPI4_SCK, PIN_SPI4_MOSI);
#endif
#if SPI_INTERFACES_COUNT > 5
  SPIClass _SPI5(PERIPH_SPI5, PIN_SPI5_MISO, PIN_SPI5_SCK, PIN_SPI5_MOSI);
#endif

