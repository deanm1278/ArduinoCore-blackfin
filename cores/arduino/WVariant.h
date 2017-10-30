#pragma once

#include <stdint.h>
#include <bf706_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions and types for pins */
typedef enum _EAnalogChannel
{
  No_ADC_Channel=-1,
  ADC_Channel0=0,
  ADC_Channel1=1,
  ADC_Channel2=2,
} EAnalogChannel ;

// Definitions for TC channels
typedef enum _ETCChannel
{
  NOT_ON_TIMER=-1,
} ETCChannel ;

// Definitions for PWM channels
typedef enum _EPWMChannel
{
  NOT_ON_PWM=-1,
} EPWMChannel ;

typedef enum _EPortType
{
  NOT_A_PORT=-1,
  EPORT_A = 0,
  EPORT_B = 1,
  EPORT_C = 2,
} EPortType ;

typedef enum
{
  EXTERNAL_INT_0 = 0,
  EXTERNAL_INT_1,
  EXTERNAL_INT_2,
  EXTERNAL_INT_3,
  EXTERNAL_INT_4,
  EXTERNAL_INT_5,
  EXTERNAL_INT_6,
  EXTERNAL_INT_7,
  EXTERNAL_INT_8,
  EXTERNAL_INT_9,
  EXTERNAL_INT_10,
  EXTERNAL_INT_11,
  EXTERNAL_INT_12,
  EXTERNAL_INT_13,
  EXTERNAL_INT_14,
  EXTERNAL_INT_15,
  EXTERNAL_INT_NMI,
  EXTERNAL_NUM_INTERRUPTS,
  NOT_AN_INTERRUPT = -1,
  EXTERNAL_INT_NONE = NOT_AN_INTERRUPT,
} EExt_Interrupts ;

typedef enum _EPioType
{
  PIO_NOT_A_PIN=-1,     /* Not under control of a peripheral. */
  PIO_MUX_0=0,
  PIO_MUX_1=1,
  PIO_MUX_2=2,
  PIO_MUX_3=3,
  PIO_MUX_INPUT_TAP=4,
} EPioType ;

/**
 * Pin Attributes to be OR-ed
 */
#define PIN_ATTR_NONE          (0UL<<0)
#define PIN_ATTR_COMBO         (1UL<<0)
#define PIN_ATTR_ANALOG        (1UL<<1)
#define PIN_ATTR_DIGITAL       (1UL<<2)
#define PIN_ATTR_PWM           (1UL<<3)
#define PIN_ATTR_TIMER         (1UL<<4)
#define PIN_ATTR_TIMER_ALT     (1UL<<5)
#define PIN_ATTR_EXTINT        (1UL<<6)

/* Types used for the table below */
typedef struct _PinDescription
{
  EPortType       ulPort ;
  uint32_t        ulPin ;
  EPioType        ulPinType ;
  uint32_t        ulPinAttribute ;
  EAnalogChannel  ulADCChannelNumber ; /* ADC Channel number */
  EPWMChannel     ulPWMChannel ;
  ETCChannel      ulTCChannel ;
  EExt_Interrupts ulExtInt ;
} PinDescription ;

/* Pins table to be instantiated into variant.cpp */
extern const PinDescription g_APinDescription[] ;

#ifdef __cplusplus
} // extern "C"
#endif
