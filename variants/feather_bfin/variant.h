#ifndef _VARIANT_FEATHER_BFIN_
#define _VARIANT_FEATHER_BFIN_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(48000000ul)

/** Master clock frequency */
//TODO: this will change
#define VARIANT_MCK			  (48000000ul)
#define VARIANT_SCLK0		  (35000000ul)

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


extern const Portgroup *g_APorts[]; 



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