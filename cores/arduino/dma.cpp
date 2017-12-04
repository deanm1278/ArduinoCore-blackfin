#include "Arduino.h"
#include "dma.h"

//simple MDMA example, single byte msg size
void mdma(uint32_t dst, uint32_t src, uint32_t size)
{
  //configure source address
  DMA[SYS_MDMA0_SRC]->ADDRSTART.reg = (uint32_t)src;
  //configure byte count
  DMA[SYS_MDMA0_SRC]->XCNT.reg = size;
  //configure step
  DMA[SYS_MDMA0_SRC]->XMOD.reg = 0x01;

  //configure destination address
  DMA[SYS_MDMA0_DST]->ADDRSTART.reg = (uint32_t)dst;
  //configure byte count
  DMA[SYS_MDMA0_DST]->XCNT.reg = size;
  //configure step
  DMA[SYS_MDMA0_DST]->XMOD.reg = 0x01;

  //enable both source and destination channels
  DMA[SYS_MDMA0_SRC]->CFG.bit.EN = 0x01;
  DMA[SYS_MDMA0_DST]->CFG.bit.EN = 0x01;
	
}
