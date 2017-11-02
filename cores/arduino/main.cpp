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

#define ARDUINO_MAIN
#include "Arduino.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Initialize C library
extern "C" void __libc_init_array(void);

extern "C" void __cxa_pure_virtual() { while (1); }

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{
  __init();

  __libc_init_array();

  initVariant();

  setup();

  for (;;)
  {
    loop();
    if (serialEventRun) serialEventRun();
  }

  return 0;
}

extern "C" {
  void UART1_STAT_Handler( void ){
    for(int j = 0; j < 5; j++){
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      for(unsigned long i=0; i<10000000UL; i++) asm("NOP;");
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
      for(unsigned long i=0; i<10000000UL; i++) asm("NOP;");
    }
  }
}