#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
	// 0..13 - Digital pins
	// ----------------------
	// 0/1 - UART (Serial1)
	{ EPORT_B, 8, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, // UART0_RX
	{ EPORT_B, 9, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, // UART0_TX

	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },
	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },
	{ EPORT_C, 0, PIO_MUX_0, PIN_ATTR_DIGITAL, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //GP_OUTPUT

	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },
	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },
	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },

	{ EPORT_C, 1, PIO_MUX_0, PIN_ATTR_DIGITAL, NOT_ON_TIMER, EXTERNAL_INT_NONE }, //GP_INPUT
	{ EPORT_A, 4, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI1 SS

	{ NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, NOT_ON_TIMER, EXTERNAL_INT_NONE },
	{ EPORT_A, 2, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI1 MOSI
	{ EPORT_A, 1, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI1 MISO
	{ EPORT_A, 0, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI1 SCLK

	//14 LED
	{ EPORT_C, 3, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE },

	//15..20 SPI2
	{ EPORT_B, 10, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 SCLK
	{ EPORT_B, 11, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 MISO
	{ EPORT_B, 12, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 MOSI
	{ EPORT_B, 13, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 D2
	{ EPORT_B, 14, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 D3
	{ EPORT_B, 15, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI2 SS

	//21..23 SPI0
	{ EPORT_B, 0, PIO_MUX_2, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI0_SCLK
	{ EPORT_B, 1, PIO_MUX_2, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI0_MISO
	{ EPORT_B, 2, PIO_MUX_2, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SPI0_MOSI

	//24..28 SPT0
	{ EPORT_C, 8, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SDTO
	{ EPORT_C, 6, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //SDTI
	{ EPORT_C, 9, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //BCLK
	{ EPORT_C, 5, PIO_MUX_0, (PIN_ATTR_DIGITAL), NOT_ON_TIMER, EXTERNAL_INT_NONE }, //FS

};

__IO Portgroup *g_APorts[NUM_PORT] = PORT_INSTS;
__IO Dmagroup *DMA[DMA_NUM] = DMA_INSTS;
__IO Sportgroup *SPORT[SPORT_NUM] = SPORT_INSTS;

Uart Serial( UART0, PIN_SERIAL_RX, PIN_SERIAL_TX ) ;
Uart Serial1( UART1, PIN_SERIAL1_RX, PIN_SERIAL1_TX ) ;

void initVariant() {
  //set clocks

  CGU0->PLLCTL.bit.PLLBPCL = 1;
  while( (CGU0->STAT.reg & 0xF) != 0x05 ); //wait
  CGU0->DIV.reg = 0x03042442;
  CGU0->CTL.reg = 0x00002000;

  while(CGU0->STAT.bit.PLLBP || CGU0->STAT.bit.CLKSALGN || (!CGU0->STAT.bit.PLOCK)); //wait for alignment and lock
}

extern "C" {

int UART0_STAT_Handler( int IQR_NUM ){
  Serial.IrqHandler();
  return IQR_NUM;
}

int UART1_STAT_Handler( int IQR_NUM ){
  Serial1.IrqHandler();
  return IQR_NUM;
}


};
