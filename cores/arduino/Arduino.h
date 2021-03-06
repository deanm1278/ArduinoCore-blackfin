/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2014 Arduino LLC.  All right reserved.

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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;

/*
#include "binary.h"
#include "itoa.h"
*/

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include "bf706_device.h"


#include "wiring_constants.h"

/*
#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )
*/

void yield( void ) ;

/* system functions */
int main( void );
void __init( void );

/* sketch */
void setup( void ) ;
void loop( void ) ;


#include "WVariant.h"
#include "dma.h"

#ifdef __cplusplus
} // extern "C"
#endif

// The following headers are for C++ only compilation
#ifdef __cplusplus
  #include "WCharacter.h"
  #include "WString.h"
  //#include "Tone.h"
  #include "WMath.h"
  #include "HardwareSerial.h"
  //#include "pulse.h"
#endif
#include "delay.h"
#ifdef __cplusplus
  #include "UART.h"
#endif

// Include board variant
#include "variant.h"

#include "wiring.h"
#include "wiring_digital.h"
//#include "wiring_analog.h"
//#include "wiring_shift.h"
//#include "WInterrupts.h"

#include "handlers.h"

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

//#define interrupts() __enable_irq()
//#define noInterrupts() __disable_irq()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

typedef int32_t q31;
typedef int32_t q28;
typedef uint32_t q16;
typedef int16_t q15;
#define _F(x) ((int) ((x)*( (1UL<<31) - 1 )))
#define _F28(x) ((int) ((x)*( (1UL<<28) - 1 )))
#define _F16(x) ((uint32_t) ((x)*( (1<<16) )))
#define _F15(x) ((int) ((x)*( (1UL<<15) - 1 )))

static inline q31 _mult32x32(q31 x, q31 y){
	q31 ret;
	__asm__ volatile("%0 = %1 * %2;" : "=d"(ret) : "d"(x), "d"(y));
	return ret;
}

static inline q16 _mult16x16(q16 x, q16 y){
	q16 ret;
	__asm__ volatile("(R5:4) = ((A1:0) = %1 * %2) (IU);\n"
					 "%0 = PACK(R5.L, R4.H);\n"
					: "=d"(ret) : "d"(x), "d"(y) : "R5", "R4");
	return ret;
}

static inline q31 _mult32x16(q31 x, q16 y){
	q16 ret;
	__asm__ volatile("(R5:4) = ((A1:0) = %1 * %2) (IU);\n"
					 "%0 = PACK(R5.L, R4.H);\n"
					: "=d"(ret) : "d"(x), "d"(y) : "R5", "R4");
	return ret;
}

#define FRACMUL(x,y) _mult32x32((x),_F(y))

#define PROFILE(name, x) { uint32_t __cycles, __deltaCycles; \
	uint32_t __mask = noInterrupts(); \
	__asm__ volatile("%0 = CYCLES;" : "=d"(__cycles)); \
	x; \
	__asm__ volatile("%0 = CYCLES;" : "=d"(__deltaCycles)); \
	Serial.print("["); Serial.print(name); Serial.print("] : "); \
	Serial.println(__deltaCycles - __cycles); __asm__ volatile("EMUEXCPT;");\
	interrupts(__mask); }

typedef struct complex_q31 {
    q31 re;
    q31 im;
} complex_q31;

typedef struct complex_q15 {
    q15 re;
    q15 im;
} complex_q15;

#define L2DATA __attribute__ ((section(".l2")))
#define RAMB __attribute__ ((section(".data2")))

#define __BKPT() __asm__ volatile("EMUEXCPT;")

/*
#if (ARDUINO_SAMD_VARIANT_COMPLIANCE >= 10606)
// Interrupts
#define digitalPinToInterrupt(P)   ( P )
#endif
*/

#endif // Arduino_h
