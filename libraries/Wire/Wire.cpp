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
	hw->CLKDIV.bit.CLKLO = (10000000/baudrate/2);
	hw->CLKDIV.bit.CLKHI = (10000000/baudrate/2);
}

void TwoWire::end() {

}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
  if(quantity == 0)
  {
    return 0;
  }

  for(int i_ = 0; i_ < 3000; i_++){ __asm__ volatile("NOP;"); }
  size_t byteRead = 0;

  rxBuffer.clear();

  hw->MSTRADDR.reg = address;
  hw->FIFOCTL.reg = 0;
  hw->MSTRCTL.reg = ((uint32_t)quantity << 6)| 0x05;

  while(byteRead < quantity){

	//TODO: we may want to add some sort of timeout here...
	uint32_t mask = noInterrupts();
	while(!hw->ISTAT.bit.RXSERV);
	rxBuffer.store_char( hw->RXDATA8.reg );

	hw->ISTAT.bit.RXSERV = 1;
	byteRead++;
	interrupts(mask);

	if(hw->MSTRSTAT.reg & 0x0C) break;
  }

  hw->ISTAT.bit.MCOMP = 1;

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

  while(hw->MSTRSTAT.bit.BUSBUSY || hw->MSTRSTAT.bit.MPROG);

  hw->FIFOCTL.reg = 0;

  uint8_t bytesAvailable = txBuffer.available() & 0xFF;

  hw->TXDATA8.reg = txBuffer.read_char();

  hw->MSTRCTL.reg = (!stopBit << 5) | ((uint32_t)bytesAvailable << 6)| 0x01;

  //send first byte
  while(!hw->ISTAT.bit.TXSERV);
  hw->ISTAT.bit.TXSERV = 1;

  // Send rest of buffer
  while( txBuffer.available() ){
	  hw->TXDATA8.reg = txBuffer.read_char();

	  while(!hw->ISTAT.bit.TXSERV){
		  if(hw->ISTAT.bit.MCOMP) break;
	  }
	  hw->ISTAT.bit.TXSERV = 1;
  }

  hw->ISTAT.bit.MCOMP = 1;

  if(stopBit) while(hw->MSTRSTAT.bit.BUSBUSY || hw->MSTRSTAT.bit.MPROG);

  //TODO: error codes

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
	//TODO: slave mode interrupt
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

