#ifndef _VARIANT_BF706_PEDAL_
#define _VARIANT_BF706_PEDAL_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(400000000ul)

/** Master clock frequency */
//TODO: this will change
#define VARIANT_MCK			  (400000000ul)

//this may need to be measured on each board
#define VARIANT_SCLK0		  (100000000ul)

#define L2_ORIGIN 			  0x08002000

#define NUM_PORT 3

#define LED_BUILTIN 	(13ul)
#define PIN_NEOPIX		(3ul)

//Serial
#define PIN_SERIAL_RX  		(0ul)
#define PIN_SERIAL_TX  		(1ul)

//Serial1
#define PIN_SERIAL1_RX  		(8ul)
#define PIN_SERIAL1_TX  		(7ul)

#define WIRE_INTERFACES_COUNT 1
#define SPI_INTERFACES_COUNT 2

#define PERIPH_SPI SPI2

//arduino SPI default is bfin peripheral SPI2
#define PIN_SPI_SCK     14
#define PIN_SPI_MISO    15
#define PIN_SPI_MOSI    16
#define PIN_SPI_D2      17
#define PIN_SPI_D3      18
#define PIN_SPI_SS      19

#define SS PIN_SPI_SS

#define PERIPH_SPI1 SPI1

#define PIN_SPI1_SCK     20
#define PIN_SPI1_MISO    21
#define PIN_SPI1_MOSI    22
#define PIN_SPI1_SS      23

#define SS1 PIN_SPI1_SS
#define PIN_CONTROLS_START PIN_SPI1_MISO
#define SPI_CONTROLS _SPI1
#define PIN_CONTROLS_SS SS1

//I2S
#define PIN_BCLK 10
#define PIN_FS 5
#define PIN_AD0 9
#define PIN_BD0 6


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "Uart.h"
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
