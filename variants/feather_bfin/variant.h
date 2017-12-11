#ifndef _VARIANT_FEATHER_BFIN_
#define _VARIANT_FEATHER_BFIN_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(400000000ul)

/** Master clock frequency */
//TODO: this will change
#define VARIANT_MCK			  (400000000ul)

//this may need to be measured on each board
#define VARIANT_SCLK0		  (107200000ul)

#define L2_ORIGIN 			  0x08002000

#define NUM_PORT 3

//Serial
#define PIN_SERIAL_RX  		(14ul)
#define PIN_SERIAL_TX  		(15ul)

// Serial1
#define PIN_SERIAL1_RX       (0ul)
#define PIN_SERIAL1_TX       (1ul)

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
