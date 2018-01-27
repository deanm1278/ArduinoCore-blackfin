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

#define noInterrupts() ({ unsigned int __rval; __asm__ __volatile__ ("cli R7; %0 = R7;" : "=r"(__rval) : : "R7"); __rval; })

#define interrupts(x) __asm__ __volatile__ ("R7 = %0; sti R7;" : : "r"(x) : "R7")

#endif
