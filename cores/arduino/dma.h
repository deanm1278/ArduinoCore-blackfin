#ifndef _LIB_DMA_H
#define _LIB_DMA_H

enum {
	SPORT0_A_DMA = 0x00,
	SPORT0_B_DMA,
	SPORT1_A_DMA,
	SPORT1_B_DMA,
	SPI0_TXDMA,
	SPI0_RXDMA,
	SPI1_TXDMA,
	SPI1_RXDMA,
	SPI2_TXDMA,
	SPI2_RXDMA,
	UART0_TXDMA,
	UART0_RXDMA,
	UART1_TXDMA,
	UART1_RXDMA,
	EPPI0_CH0_DMA,
	EPPI0_CH1_DMA,
	SYS_MDMA0_SRC,
	SYS_MDMA0_DST,
	SYS_MDMA1_SRC,
	SYS_MDMA1_DST,
	SYS_MDMA2_SRC,
	SYS_MDMA2_DST,
};

#define NUM_MDMA_CHANNELS 3

enum {
	DMA_MSIZE_1_BYTES = 0,
	DMA_MSIZE_2_BYTES,
	DMA_MSIZE_4_BYTES,
	DMA_MSIZE_8_BYTES,
	DMA_MSIZE_16_BYTES,
	DMA_MSIZE_32_BYTES,
};

enum {
	DMA_CFG_DISABLE = 0,
	DMA_CFG_ENABLE
};

enum {
	DMA_CFG_FLOW_STOP = 0,
	DMA_CFG_FLOW_AUTO,
	DMA_CFG_FLOW_DSCL = 4,
	DMA_CFG_FLOW_DSCA,
	DMA_CFG_FLOW_ON_DEMAND_LIST,
	DMA_CFG_FLOW_ON_DEMAND_ARRAY,
};

enum {
	DMA_CFG_PSIZE_1_BYTES = 0,
	DMA_CFG_PSIZE_2_BYTES,
	DMA_CFG_PSIZE_4_BYTES,
	DMA_CFG_PSIZE_8_BYTES,
};

enum {
	DMA_CFG_WNR_READ_FROM_MEM = 0,
	DMA_CFG_WNR_WRITE_TO_MEM,
};

enum{
	DMA_CFG_INT_NONE = 0,
	DMA_CFG_INT_X_COUNT,
	DMA_CFG_INT_Y_COUNT,
	DMA_CFG_INT_PERIPHERAL
};

typedef struct {
	volatile DMA_DSCPTR_NXT_Type		DSCPTR_NXT;		/**< \brief DMA0 Pointer to Next Initial Descriptor */
	volatile DMA_ADDRSTART_Type		ADDRSTART;		/**< \brief DMA0 Start Address of Current Buffer */
	volatile DMA_CFG_Type		CFG;		/**< \brief DMA0 Configuration Register */
	volatile DMA_XCNT_Type		XCNT;		/**< \brief DMA0 Inner Loop Count Start Value */
	volatile DMA_XMOD_Type		XMOD;		/**< \brief DMA0 Inner Loop Address Increment */
	volatile DMA_YCNT_Type		YCNT;		/**< \brief DMA0 Outer Loop Count Start Value (2D only) */
	volatile DMA_YMOD_Type		YMOD;		/**< \brief DMA0 Outer Loop Address Increment (2D only) */
} PDMADescriptor;

void mdma(uint32_t dst, uint32_t src, uint32_t size);

#endif
