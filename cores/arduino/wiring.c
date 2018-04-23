/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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
#include "handlers.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * System Core Clock is at 48mhz at reset (I think)
 */
uint32_t SystemCoreClock=48000000ul ;

void __init( void )
{
  //SEC_Global->SEC0_GCTL.bit.RESET = 1;
  //SCI->SEC0_CCTL0.bit.RESET = 1;

  //systick timer enable
  TMR->TCNTL.bit.PWR = 1;
  TMR->TCNTL.bit.AUTORLD = 1;
  TMR->TSCALE.reg = 1; //decrement every 2 clock cycles
  TMR->TPERIOD.reg = (VARIANT_MCK)/1000; //1 per ms
  TMR->TCNTL.bit.EN = 1;

  //enable interrupts
  SEC_Global->SEC0_GCTL.bit.EN = 1;
  SCI->SEC0_CCTL0.bit.EN = 1;
}

#ifdef __cplusplus
}
#endif
