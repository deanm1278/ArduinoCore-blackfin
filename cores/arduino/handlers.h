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

#endif
