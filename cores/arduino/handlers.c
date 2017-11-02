#include <bf706_device.h>
#include "handlers.h"

/* Default empty handler */
void Dummy_Handler(void)
{
	for(int j = 0; j < 5; j++){
      PORTB->DIR_SET.bit.PX4 = 1;
      for(unsigned long i=0; i<10000000UL; i++) asm("NOP;");
      PORTB->DIR_CLR.bit.PX4 = 1;
      for(unsigned long i=0; i<10000000UL; i++) asm("NOP;");
    }
}

void Reserved1_Handler			( void );
void SEC0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CGU0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDOG0_EXP_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void L2CTL0_ECC_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void Reserved2_Handler			( void );
void SYS_C0_DBL_FAULT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_C0_HW_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_C0_NMI_L1_PARITY_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void L2CTL0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void Reserved3_Handler			( void );
void TIMER0_TMR0_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR1_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR2_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR3_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR4_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR5_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR6_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_TMR7_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TIMER0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PINT0_BLOCK_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PINT1_BLOCK_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PINT2_BLOCK_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EPPI0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EPPI0_CH0_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EPPI0_CH1_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_DMAC_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CNT0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT0_A_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT0_A_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT0_B_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT0_B_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT1_A_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT1_A_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT1_B_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPORT1_B_DMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_TXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_RXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI1_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI1_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI1_TXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI1_RXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI2_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI2_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI2_TXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI2_RXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_TXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_RXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART1_STAT_Handler			( void );
void UART1_TXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART1_RXDMA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA0_SRC_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA0_DST_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA1_SRC_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA1_DST_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA2_SRC_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_MDMA2_DST_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HADC0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI0_DATA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CRC0_DCNTEXP_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CRC0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CRC1_DCNTEXP_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CRC1_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PKTE0_IRQ_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PKIC0_IRQ_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void Reserved4_Handler			( void );
void Reserved5_Handler			( void );
void OTPC0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MSI0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SMPU0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SMPU1_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void Reserved6_Handler			( void );
void SPU0_INT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USB0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USB0_DATA_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRU0_SLV0_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRU0_SLV1_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRU0_SLV2_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRU0_SLV3_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CGU0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DPM0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPIHP0_ERR_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_SOFT0_INT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_SOFT1_INT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_SOFT2_INT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYS_SOFT3_INT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN0_RX_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN0_TX_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN0_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_RX_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_TX_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_STAT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CTI_C0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU0_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU1_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU2_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU3_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU4_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU5_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU6_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SWU7_EVT_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TAPC0_KEYFAIL_Handler			( void ) __attribute__ ((weak, alias("Dummy_Handler")));

__attribute__ ((section(".isr_vector"))) const DeviceVectors exception_table =
{
	(void*) (0UL),
	(void*) SEC0_ERR_Handler,
	(void*) CGU0_EVT_Handler,
	(void*) WDOG0_EXP_Handler,
	(void*) L2CTL0_ECC_ERR_Handler,
	(void*) (0UL),
	(void*) SYS_C0_DBL_FAULT_Handler,
	(void*) SYS_C0_HW_ERR_Handler,
	(void*) SYS_C0_NMI_L1_PARITY_ERR_Handler,
	(void*) L2CTL0_EVT_Handler,
	(void*) (0UL),
	(void*) TIMER0_TMR0_Handler,
	(void*) TIMER0_TMR1_Handler,
	(void*) TIMER0_TMR2_Handler,
	(void*) TIMER0_TMR3_Handler,
	(void*) TIMER0_TMR4_Handler,
	(void*) TIMER0_TMR5_Handler,
	(void*) TIMER0_TMR6_Handler,
	(void*) TIMER0_TMR7_Handler,
	(void*) TIMER0_STAT_Handler,
	(void*) PINT0_BLOCK_Handler,
	(void*) PINT1_BLOCK_Handler,
	(void*) PINT2_BLOCK_Handler,
	(void*) EPPI0_STAT_Handler,
	(void*) EPPI0_CH0_DMA_Handler,
	(void*) EPPI0_CH1_DMA_Handler,
	(void*) SYS_DMAC_ERR_Handler,
	(void*) CNT0_STAT_Handler,
	(void*) SPORT0_A_STAT_Handler,
	(void*) SPORT0_A_DMA_Handler,
	(void*) SPORT0_B_STAT_Handler,
	(void*) SPORT0_B_DMA_Handler,
	(void*) SPORT1_A_STAT_Handler,
	(void*) SPORT1_A_DMA_Handler,
	(void*) SPORT1_B_STAT_Handler,
	(void*) SPORT1_B_DMA_Handler,
	(void*) SPI0_ERR_Handler,
	(void*) SPI0_STAT_Handler,
	(void*) SPI0_TXDMA_Handler,
	(void*) SPI0_RXDMA_Handler,
	(void*) SPI1_ERR_Handler,
	(void*) SPI1_STAT_Handler,
	(void*) SPI1_TXDMA_Handler,
	(void*) SPI1_RXDMA_Handler,
	(void*) SPI2_ERR_Handler,
	(void*) SPI2_STAT_Handler,
	(void*) SPI2_TXDMA_Handler,
	(void*) SPI2_RXDMA_Handler,
	(void*) UART0_STAT_Handler,
	(void*) UART0_TXDMA_Handler,
	(void*) UART0_RXDMA_Handler,
	(void*) UART1_STAT_Handler,
	(void*) UART1_TXDMA_Handler,
	(void*) UART1_RXDMA_Handler,
	(void*) SYS_MDMA0_SRC_Handler,
	(void*) SYS_MDMA0_DST_Handler,
	(void*) SYS_MDMA1_SRC_Handler,
	(void*) SYS_MDMA1_DST_Handler,
	(void*) SYS_MDMA2_SRC_Handler,
	(void*) SYS_MDMA2_DST_Handler,
	(void*) HADC0_EVT_Handler,
	(void*) RTC0_EVT_Handler,
	(void*) TWI0_DATA_Handler,
	(void*) CRC0_DCNTEXP_Handler,
	(void*) CRC0_ERR_Handler,
	(void*) CRC1_DCNTEXP_Handler,
	(void*) CRC1_ERR_Handler,
	(void*) PKTE0_IRQ_Handler,
	(void*) PKIC0_IRQ_Handler,
	(void*) (0UL),
	(void*) (0UL),
	(void*) OTPC0_ERR_Handler,
	(void*) MSI0_STAT_Handler,
	(void*) SMPU0_ERR_Handler,
	(void*) SMPU1_ERR_Handler,
	(void*) (0UL),
	(void*) SPU0_INT_Handler,
	(void*) USB0_STAT_Handler,
	(void*) USB0_DATA_Handler,
	(void*) TRU0_SLV0_Handler,
	(void*) TRU0_SLV1_Handler,
	(void*) TRU0_SLV2_Handler,
	(void*) TRU0_SLV3_Handler,
	(void*) CGU0_ERR_Handler,
	(void*) DPM0_EVT_Handler,
	(void*) SPIHP0_ERR_Handler,
	(void*) SYS_SOFT0_INT_Handler,
	(void*) SYS_SOFT1_INT_Handler,
	(void*) SYS_SOFT2_INT_Handler,
	(void*) SYS_SOFT3_INT_Handler,
	(void*) CAN0_RX_Handler,
	(void*) CAN0_TX_Handler,
	(void*) CAN0_STAT_Handler,
	(void*) CAN1_RX_Handler,
	(void*) CAN1_TX_Handler,
	(void*) CAN1_STAT_Handler,
	(void*) CTI_C0_EVT_Handler,
	(void*) SWU0_EVT_Handler,
	(void*) SWU1_EVT_Handler,
	(void*) SWU2_EVT_Handler,
	(void*) SWU3_EVT_Handler,
	(void*) SWU4_EVT_Handler,
	(void*) SWU5_EVT_Handler,
	(void*) SWU6_EVT_Handler,
	(void*) SWU7_EVT_Handler,
	(void*) TAPC0_KEYFAIL_Handler,
};