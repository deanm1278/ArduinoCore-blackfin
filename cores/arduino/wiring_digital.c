/*
  Copyright (c) 2015 Arduino LLC., 2017 Dean Miller  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

//TODO: digital stuff once PORTS are set to same object

void pinMode( uint32_t ulPin, uint32_t ulMode )
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }
  EPortType port = g_APinDescription[ulPin].ulPort;
  uint32_t pin = g_APinDescription[ulPin].ulPin;
  uint32_t pinMask = (1ul << pin);

  //enable GPIO mode
  g_APorts[port]->FER_CLR.reg = pinMask;

  // Set pin mode
  switch ( ulMode )
  {
    case INPUT:
      // Set pin to input mode
      g_APorts[port]->DIR_CLR.reg = pinMask;
    break ;

    case INPUT_PULLUP:
      // Set pin to input mode with pull-up resistor enabled
    break ;

    case INPUT_PULLDOWN:
      // Set pin to input mode with pull-down resistor enabled
    break ;

    case OUTPUT:
      // Set pin to output mode
      g_APorts[port]->DIR_SET.reg = pinMask;
    break ;

    default:
      // do nothing
    break ;
  }
}

void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }

  EPortType port = g_APinDescription[ulPin].ulPort;
  uint32_t pin = g_APinDescription[ulPin].ulPin;
  uint32_t pinMask = (1ul << pin);

  switch ( ulVal )
  {
    case LOW:{
      g_APorts[port]->DATA_CLR.reg = pinMask;
      break ;
    }

    default:{
	   g_APorts[port]->DATA_SET.reg = pinMask;
	   break ;
    }
  }

  return ;
}

int digitalRead( uint32_t ulPin )
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
  {
    return LOW ;
  }

  //TODO: read input

  return LOW ;
}

#ifdef __cplusplus
}
#endif

