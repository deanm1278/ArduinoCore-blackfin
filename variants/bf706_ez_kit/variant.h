#ifndef _VARIANT_BF706_EZ_KIT_
#define _VARIANT_BF706_EZ_KIT_

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

#define LED_BUILTIN 	(14ul)

//Serial
#define PIN_SERIAL_RX  		(0ul)
#define PIN_SERIAL_TX  		(1ul)

// Serial1
#define PIN_SERIAL1_RX       (8ul)
#define PIN_SERIAL1_TX       (4ul)

#define WIRE_INTERFACES_COUNT 1
#define SPI_INTERFACES_COUNT 2

#define PERIPH_SPI SPI1

//arduino SPI default is bfin peripheral SPI1
#define PIN_SPI_SCK     13
#define PIN_SPI_MISO    12
#define PIN_SPI_MOSI    11
#define PIN_SPI_SS      9

#define SS PIN_SPI_SS

#define PERIPH_SPI1 SPI2

//arduino SPI1 is bfin peripheral SPI2 (confusing but helps compatibility)
#define PIN_SPI1_SCK     15
#define PIN_SPI1_MISO    16
#define PIN_SPI1_MOSI    17
#define PIN_SPI1_D2		 18
#define PIN_SPI1_D3		 19
#define PIN_SPI1_SS      20

#define SS1 PIN_SPI1_SS


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
