#include <Arduino.h>
#include "I2S.h"
#include "variant.h"
#include "wiring_private.h"
#include "dma.h"

I2S::I2S(Sportgroup *sport, uint8_t _pinCLK, uint8_t _pinFS, uint8_t _pinAD0, uint8_t _pinBD0) : hw(sport) , 
	_ucPinCLK(_pinCLK) , _ucPinFS(_pinFS) , _ucPinAD0(_pinAD0) , _ucPinBD0(_pinBD0) {}

bool I2S::begin(uint32_t clkRate, uint32_t fsRate, uint8_t wordLength)
{
	pinPeripheral(_ucPinCLK, g_APinDescription[_ucPinCLK].ulPinType);
  	pinPeripheral(_ucPinFS, g_APinDescription[_ucPinFS].ulPinType);
  	pinPeripheral(_ucPinAD0, g_APinDescription[_ucPinAD0].ulPinType);
  	pinPeripheral(_ucPinBD0, g_APinDescription[_ucPinBD0].ulPinType);

  	//clear regs
  	hw->CTL_A.reg = 0;
  	hw->MCTL_A.reg = 0;

  	hw->DIV_A.bit.FSDIV = (clkRate / fsRate) - 1;
	hw->DIV_A.bit.CLKDIV = (VARIANT_SCLK0 / clkRate) - 1;

	 //set channel A to be transmit
  	hw->CTL_A.bit.SPTRAN = 1;

  	hw->CTL_A.bit.ICLK = 1; //internal clock mode
  	hw->CTL_A.bit.IFS = 1;
  	//set to I2S mode
  	hw->CTL_A.bit.OPMODE = 1;
  	hw->CTL_A.bit.LAFS = 0;
  	hw->CTL_A.bit.LSBF = 0; //MSB first data
  	hw->CTL_A.bit.CKRE = 1;
  	hw->CTL_A.bit.SLEN = wordLength - 1;

  	//hw->CTL_A.bit.TFIEN = 1;

  	//enable primary and disable secondary
  	hw->CTL_A.bit.SPENPRI = 1;
  	hw->CTL_A.bit.SPENSEC = 0;

  	hw->MCTL_A.bit.MCE = 0;

  	//channel B
  	hw->CTL_B.reg = 0;
  	hw->MCTL_B.reg = 0;

  	//set channel B to be receive
  	hw->CTL_B.bit.SPTRAN = 0;
  	hw->CTL_B.bit.ICLK = 0; //receive channel is tied to transmit channel clock in hardware
  	hw->CTL_B.bit.IFS = 0; //receive channel fs is tied to transmit channel in hardware

  	hw->CTL_B.bit.OPMODE = 1;
  	hw->CTL_B.bit.LAFS = 0;
  	hw->CTL_B.bit.LSBF = 0; //MSB first data
  	hw->CTL_B.bit.CKRE = 1;
  	hw->CTL_B.bit.SLEN = wordLength - 1;

  	hw->CTL2_B.reg = 0x03; //share fs and clk

  	//enable primary and disable secondary
  	hw->CTL_B.bit.SPENPRI = 1;
  	hw->CTL_B.bit.SPENSEC = 0;

  	hw->MCTL_B.bit.MCE = 0;

  	return true;
}

//Endlessly DMA out the passed buffer. Must be interleaved LRLR
void I2S::beginDMAAutobuffer(uint32_t addr, uint32_t count, bool tx)
{
	uint8_t ch;
	if(tx){
		ch = SPORT0_A_DMA;
		if(hw == SPORT1) ch = SPORT1_A_DMA;
	}
	else{
		ch = SPORT0_B_DMA;
		if(hw == SPORT1) ch = SPORT1_B_DMA;
	}

	DMA[ch]->ADDRSTART.reg = (uint32_t)addr;

	//TODO: set based on wordLength
	DMA[ch]->CFG.bit.MSIZE = DMA_MSIZE_4_BYTES;
	DMA[ch]->XCNT.reg = count;
	DMA[ch]->XMOD.reg = 4; //4 bytes

	if(tx) DMA[ch]->CFG.bit.WNR = DMA_CFG_WNR_READ_FROM_MEM;
	else DMA[ch]->CFG.bit.WNR = DMA_CFG_WNR_WRITE_TO_MEM;

	DMA[ch]->CFG.bit.FLOW = DMA_CFG_FLOW_AUTO; //autobuffer mode
	DMA[ch]->CFG.bit.PSIZE = DMA_CFG_PSIZE_4_BYTES;
	DMA[ch]->CFG.bit.EN = DMA_CFG_ENABLE; //enable
}

/*
//TODO: this doesn't work quite yet, DMA seems to not be able to fetch descriptor
void I2S::beginDMAPassThrough(uint32_t addrPing, uint32_t addrPong, uint32_t count,
		PDMADescriptor *pingTx, PDMADescriptor *pingRx,
		PDMADescriptor *pongTx, PDMADescriptor *pongRx)
{
	uint8_t chTx = SPORT0_A_DMA;
	uint8_t chRx = SPORT0_B_DMA;
	if(hw == SPORT1){
		chTx = SPORT1_A_DMA;
		chRx = SPORT1_B_DMA;
	}

	pingTx->CFG.bit.MSIZE = DMA_MSIZE_4_BYTES;
	pingTx->CFG.bit.FLOW = DMA_CFG_FLOW_DSCL;
	pingTx->CFG.bit.PSIZE = DMA_CFG_PSIZE_4_BYTES;
	pingTx->CFG.bit.EN = DMA_CFG_ENABLE; //enable

	pingTx->XCNT.reg = count;
	pingTx->XMOD.reg = 4; //4 bytes

	memcpy(pongTx, pingTx, sizeof(PDMADescriptor));
	memcpy(pingRx, pingTx, sizeof(PDMADescriptor));
	memcpy(pongRx, pingTx, sizeof(PDMADescriptor));

	pingTx->ADDRSTART.reg = (uint32_t)addrPing;
	pingRx->ADDRSTART.reg = (uint32_t)addrPong;
	pongTx->ADDRSTART.reg = (uint32_t)addrPong;
	pongRx->ADDRSTART.reg = (uint32_t)addrPing;

	pingTx->DSCPTR_NXT.reg = (uint32_t)pongTx;
	pongTx->DSCPTR_NXT.reg = (uint32_t)pingTx;

	pingRx->DSCPTR_NXT.reg = (uint32_t)pongRx;
	pongRx->DSCPTR_NXT.reg = (uint32_t)pingRx;

	pingTx->CFG.bit.WNR = DMA_CFG_WNR_READ_FROM_MEM;
	pongTx->CFG.bit.WNR = DMA_CFG_WNR_READ_FROM_MEM;

	pingRx->CFG.bit.WNR = DMA_CFG_WNR_WRITE_TO_MEM;
	pongRx->CFG.bit.WNR = DMA_CFG_WNR_WRITE_TO_MEM;

	DMA[chTx]->DSCPTR_NXT.reg = (uint32_t)pingTx;
	DMA[chRx]->DSCPTR_NXT.reg = (uint32_t)pingRx;

	DMA[chTx]->CFG.bit.WNR = DMA_CFG_WNR_READ_FROM_MEM;
	DMA[chRx]->CFG.bit.WNR = DMA_CFG_WNR_WRITE_TO_MEM;

	DMA[chTx]->CFG.bit.FLOW = DMA_CFG_FLOW_DSCL;
	DMA[chRx]->CFG.bit.FLOW = DMA_CFG_FLOW_DSCL;

	DMA[chTx]->CFG.bit.PSIZE = DMA_CFG_PSIZE_4_BYTES;
	DMA[chRx]->CFG.bit.PSIZE = DMA_CFG_PSIZE_4_BYTES;

	DMA[chTx]->CFG.bit.EN = DMA_CFG_ENABLE; //enable
	DMA[chRx]->CFG.bit.EN = DMA_CFG_ENABLE; //enable
}
*/

void I2S::writeDirect(int32_t l, int32_t r)
{
	hw->TXPRI_A.reg = l;
	hw->TXPRI_A.reg = r;
}
