#ifndef _VARIANT_H_
#define _VARIANT_H_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(400000000ul)

/** Master clock frequency */
#define VARIANT_MCK			  (400000000ul)

//this may need to be measured on each board
#define VARIANT_SCLK0		  (100000000ul)

#define L2_ORIGIN 			  0x08002000

#define NUM_PORT 3

#define LED_BUILTIN 	(13ul)

//Serial
#define PIN_SERIAL_RX  		(14ul)
#define PIN_SERIAL_TX  		(15ul)

// Serial1
#define PIN_SERIAL1_RX       (0ul)
#define PIN_SERIAL1_TX       (1ul)

#define WIRE_INTERFACES_COUNT 1
#define SPI_INTERFACES_COUNT 1

#define PERIPH_SPI SPI2

#define PIN_SPI_SCK     16
#define PIN_SPI_MISO    17
#define PIN_SPI_MOSI    18
#define PIN_SPI_D2      19
#define PIN_SPI_D3      20
#define PIN_SPI_SS      21

//I2S
#define PIN_BCLK 25
#define PIN_FS 22
#define PIN_AD0 24
#define PIN_BD0 23

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "UART.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


extern __IO Portgroup *g_APorts[];
extern __IO Dmagroup *DMA[];
extern __IO Sportgroup *SPORT[];


#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

extern Uart Serial;
extern Uart Serial1;

#endif

#endif
