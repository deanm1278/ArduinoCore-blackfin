/*
 * TWI/I2C library for Arduino Zero
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
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

extern "C" {
#include <string.h>
}

#include <Arduino.h>
#include <wiring_private.h>

#include "Wire.h"

TwoWire::TwoWire(Twi0 *twi)
{
	hw = twi;
}

void TwoWire::begin(void) {

	hw->CTL.bit.PRESCALE = VARIANT_SCLK0/10000000 + 1;

	setClock(TWI_CLOCK);

	hw->CTL.bit.EN = 1;
}

void TwoWire::begin(uint8_t address) {

}

void TwoWire::setClock(uint32_t baudrate) {
	hw->CLKDIV.bit.CLKLO = (10000000/baudrate);
	hw->CLKDIV.bit.CLKHI = (10000000/baudrate);
}

void TwoWire::end() {

}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
  if(quantity == 0)
  {
    return 0;
  }

  size_t byteRead = 0;

  rxBuffer.clear();

  hw->MSTRADDR.reg = address;

  return byteRead;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity)
{
  return requestFrom(address, quantity, true);
}

void TwoWire::beginTransmission(uint8_t address) {
  // save address of target and clear buffer
  txAddress = address;
  txBuffer.clear();

  transmissionBegun = true;

  hw->MSTRADDR.reg = address;
}

// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error
uint8_t TwoWire::endTransmission(bool stopBit)
{
  transmissionBegun = false ;

  hw->FIFOCTL.reg = 0;

  hw->TXDATA8.reg = txBuffer.read_char();

  hw->MSTRCTL.reg = 0x00;

  hw->MSTRCTL.bit.DCNT = 0xFF; //disable counter
  hw->MSTRCTL.bit.EN = 1;

  // Send all buffer
  while( txBuffer.available() ){
	  while(hw->FIFOSTAT.bit.TXSTAT);
	  hw->TXDATA8.reg = txBuffer.read_char();
  }

  hw->MSTRCTL.bit.STOP = 1;
  hw->MSTRCTL.bit.EN = 0;

  return 0;
}

uint8_t TwoWire::endTransmission()
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t ucData)
{
  // No writing, without begun transmission or a full buffer
  if ( !transmissionBegun || txBuffer.isFull() )
  {
    return 0 ;
  }

  txBuffer.store_char( ucData ) ;

  return 1 ;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  //Try to store all data
  for(size_t i = 0; i < quantity; ++i)
  {
    //Return the number of data stored, when the buffer is full (if write return 0)
    if(!write(data[i]))
      return i;
  }

  //All data stored
  return quantity;
}

int TwoWire::available(void)
{
  return rxBuffer.available();
}

int TwoWire::read(void)
{
  return rxBuffer.read_char();
}

int TwoWire::peek(void)
{
  return rxBuffer.peek();
}

void TwoWire::flush(void)
{
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}

void TwoWire::onReceive(void(*function)(int))
{
  onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void))
{
  onRequestCallback = function;
}

void TwoWire::onService(void)
{

}

#if WIRE_INTERFACES_COUNT > 0
  /* In case new variant doesn't define these macros
   *
   * These values should be different on some variants!
   */
  #ifndef PERIPH_WIRE
    #define PERIPH_WIRE          TWI0
    #define WIRE_IT_HANDLER      TWI0_DATA_Handler
  #endif // PERIPH_WIRE
  TwoWire Wire(PERIPH_WIRE);

  void WIRE_IT_HANDLER(void) {
    Wire.onService();
  }
#endif

