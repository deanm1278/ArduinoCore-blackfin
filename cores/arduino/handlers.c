#include <bf706_device.h>
#include "handlers.h"

/* Default empty handler */
int Dummy_Handler(int IQR_NUM)
{
	for(int j = 0; j < 5; j++){
      PORTB->DATA_SET.bit.PX4 = 1;
      for(unsigned long i=0; i<1000000UL; i++) asm("NOP;");
      PORTB->DATA_CLR.bit.PX4 = 1;
      for(unsigned long i=0; i<10000000UL; i++) asm("NOP;");
    }
}

int Reserved1_Handler			( int );
int SEC0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CGU0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int WDOG0_EXP_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int L2CTL0_ECC_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int Reserved2_Handler			( int );
int SYS_C0_DBL_FAULT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_C0_HW_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_C0_NMI_L1_PARITY_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int L2CTL0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int Reserved3_Handler			( int );
int TIMER0_TMR0_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR1_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR2_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR3_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR4_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR5_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR6_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_TMR7_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TIMER0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int PINT0_BLOCK_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int PINT1_BLOCK_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int PINT2_BLOCK_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int EPPI0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int EPPI0_CH0_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int EPPI0_CH1_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_DMAC_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CNT0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT0_A_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT0_A_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT0_B_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT0_B_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT1_A_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT1_A_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT1_B_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPORT1_B_DMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI0_TXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI0_RXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI1_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI1_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI1_TXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI1_RXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI2_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI2_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI2_TXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPI2_RXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int UART0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int UART0_TXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int UART0_RXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int UART1_STAT_Handler			( int );
int UART1_TXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int UART1_RXDMA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA0_SRC_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA0_DST_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA1_SRC_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA1_DST_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA2_SRC_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_MDMA2_DST_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int HADC0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int RTC0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TWI0_DATA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CRC0_DCNTEXP_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CRC0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CRC1_DCNTEXP_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CRC1_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int PKTE0_IRQ_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int PKIC0_IRQ_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int Reserved4_Handler			( int );
int Reserved5_Handler			( int );
int OTPC0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int MSI0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SMPU0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SMPU1_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int Reserved6_Handler			( int );
int SPU0_INT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int USB0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int USB0_DATA_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TRU0_SLV0_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TRU0_SLV1_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TRU0_SLV2_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TRU0_SLV3_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CGU0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int DPM0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SPIHP0_ERR_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_SOFT0_INT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_SOFT1_INT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_SOFT2_INT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SYS_SOFT3_INT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN0_RX_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN0_TX_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN0_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN1_RX_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN1_TX_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CAN1_STAT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int CTI_C0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU0_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU1_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU2_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU3_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU4_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU5_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU6_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int SWU7_EVT_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));
int TAPC0_KEYFAIL_Handler			( int ) __attribute__ ((weak, alias("Dummy_Handler")));

//__attribute__ ((section(".isr_vector"))) int (*exception_table[106])( int ) =
int const (*exception_table[106])( int ) =
{
	  (0UL),
	  SEC0_ERR_Handler,
	  CGU0_EVT_Handler,
	  WDOG0_EXP_Handler,
	  L2CTL0_ECC_ERR_Handler,
	  (0UL),
	  SYS_C0_DBL_FAULT_Handler,
	  SYS_C0_HW_ERR_Handler,
	  SYS_C0_NMI_L1_PARITY_ERR_Handler,
	  L2CTL0_EVT_Handler,
	  (0UL),
	  TIMER0_TMR0_Handler,
	  TIMER0_TMR1_Handler,
	  TIMER0_TMR2_Handler,
	  TIMER0_TMR3_Handler,
	  TIMER0_TMR4_Handler,
	  TIMER0_TMR5_Handler,
	  TIMER0_TMR6_Handler,
	  TIMER0_TMR7_Handler,
	  TIMER0_STAT_Handler,
	  PINT0_BLOCK_Handler,
	  PINT1_BLOCK_Handler,
	  PINT2_BLOCK_Handler,
	  EPPI0_STAT_Handler,
	  EPPI0_CH0_DMA_Handler,
	  EPPI0_CH1_DMA_Handler,
	  SYS_DMAC_ERR_Handler,
	  CNT0_STAT_Handler,
	  SPORT0_A_STAT_Handler,
	  SPORT0_A_DMA_Handler,
	  SPORT0_B_STAT_Handler,
	  SPORT0_B_DMA_Handler,
	  SPORT1_A_STAT_Handler,
	  SPORT1_A_DMA_Handler,
	  SPORT1_B_STAT_Handler,
	  SPORT1_B_DMA_Handler,
	  SPI0_ERR_Handler,
	  SPI0_STAT_Handler,
	  SPI0_TXDMA_Handler,
	  SPI0_RXDMA_Handler,
	  SPI1_ERR_Handler,
	  SPI1_STAT_Handler,
	  SPI1_TXDMA_Handler,
	  SPI1_RXDMA_Handler,
	  SPI2_ERR_Handler,
	  SPI2_STAT_Handler,
	  SPI2_TXDMA_Handler,
	  SPI2_RXDMA_Handler,
	  UART0_STAT_Handler,
	  UART0_TXDMA_Handler,
	  UART0_RXDMA_Handler,
	  UART1_STAT_Handler,
	  UART1_TXDMA_Handler,
	  UART1_RXDMA_Handler,
	  SYS_MDMA0_SRC_Handler,
	  SYS_MDMA0_DST_Handler,
	  SYS_MDMA1_SRC_Handler,
	  SYS_MDMA1_DST_Handler,
	  SYS_MDMA2_SRC_Handler,
	  SYS_MDMA2_DST_Handler,
	  HADC0_EVT_Handler,
	  RTC0_EVT_Handler,
	  TWI0_DATA_Handler,
	  CRC0_DCNTEXP_Handler,
	  CRC0_ERR_Handler,
	  CRC1_DCNTEXP_Handler,
	  CRC1_ERR_Handler,
	  PKTE0_IRQ_Handler,
	  PKIC0_IRQ_Handler,
	  (0UL),
	  (0UL),
	  OTPC0_ERR_Handler,
	  MSI0_STAT_Handler,
	  SMPU0_ERR_Handler,
	  SMPU1_ERR_Handler,
	  (0UL),
	  SPU0_INT_Handler,
	  USB0_STAT_Handler,
	  USB0_DATA_Handler,
	  TRU0_SLV0_Handler,
	  TRU0_SLV1_Handler,
	  TRU0_SLV2_Handler,
	  TRU0_SLV3_Handler,
	  CGU0_ERR_Handler,
	  DPM0_EVT_Handler,
	  SPIHP0_ERR_Handler,
	  SYS_SOFT0_INT_Handler,
	  SYS_SOFT1_INT_Handler,
	  SYS_SOFT2_INT_Handler,
	  SYS_SOFT3_INT_Handler,
	  CAN0_RX_Handler,
	  CAN0_TX_Handler,
	  CAN0_STAT_Handler,
	  CAN1_RX_Handler,
	  CAN1_TX_Handler,
	  CAN1_STAT_Handler,
	  CTI_C0_EVT_Handler,
	  SWU0_EVT_Handler,
	  SWU1_EVT_Handler,
	  SWU2_EVT_Handler,
	  SWU3_EVT_Handler,
	  SWU4_EVT_Handler,
	  SWU5_EVT_Handler,
	  SWU6_EVT_Handler,
	  SWU7_EVT_Handler,
	  TAPC0_KEYFAIL_Handler,
};
