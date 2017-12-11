#ifndef _HANDLERS_H
#define _HANDLERS_H

//TODO: clean these up
static inline void enableIRQ(uint8_t num)
{
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) |= 0x05;
}

static inline void disableIRQ(uint8_t num)
{
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) &= ~(0x05);
}

static inline void noInterrupts( uint32_t *imask ){
	__asm__ volatile ("cli %0;" : "=r"(imask) );
}

static inline void interrupts( uint32_t imask ){
	__asm__ volatile ("sti %0;" : : "r"(imask) );
}

#endif
