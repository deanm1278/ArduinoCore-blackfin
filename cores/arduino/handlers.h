#ifndef _HANDLERS_H
#define _HANDLERS_H

#define IRQ_MAX_PRIORITY 0xFF

static inline void raiseIRQ(uint8_t num)
{
	SEC_Global->SEC0_RAISE.bit.SID = num;
}

//TODO: clean these up
static inline void enableIRQ(uint8_t num)
{
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) |= 0x05;
}

static inline void disableIRQ(uint8_t num)
{
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) &= ~(0x05);
}

static inline void setIRQPriority(uint8_t num, uint8_t prio)
{
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) &= ~(0xFF00);
	*(volatile uint32_t *)(((uint32_t)&SSI->SEC0_SCTL0) + (num << 3)) |= (prio << 8);
}

static inline void noInterrupts( uint32_t *imask ){
	__asm__ volatile ("cli %0;" : "=r"(imask) );
}

static inline void interrupts( uint32_t imask ){
	__asm__ volatile ("sti %0;" : : "r"(imask) );
}

#endif
