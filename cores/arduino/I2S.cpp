#include <Arduino.h>
#include "I2S.h"
#include "variant.h"
#include "wiring_private.h"

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
	hw->DIV_A.bit.CLKDIV = VARIANT_SCLK0 / (clkRate + 1);

	 //set channel A to be transmit
  	hw->CTL_A.bit.SPTRAN = 1;
  	//enable primary and disable secondary
  	hw->CTL_A.bit.SPENPRI = 1;
  	hw->CTL_A.bit.SPENSEC = 0;
  	hw->CTL_A.bit.ICLK = 1; //internal clock mode
  	hw->CTL_A.bit.IFS = 1;
  	//set to I2S mode
  	hw->CTL_A.bit.OPMODE = 1;
  	hw->CTL_A.bit.LAFS = 0;
  	hw->CTL_A.bit.LSBF = 0; //MSB first data
  	hw->CTL_A.bit.CKRE = 1;
  	hw->CTL_A.bit.SLEN = wordLength - 1;

  	hw->MCTL_A.bit.MCE = 0;

  	//channel B
  	hw->CTL_B.reg = 0;
  	hw->MCTL_B.reg = 0;

  	hw->CTL_B.bit.ICLK = 0; //receive channel is tied to transmit channel clock in hardware
  	//set channel B to be receive
  	hw->CTL_B.bit.SPTRAN = 0;
  	//enable primary and disable secondary
  	hw->CTL_B.bit.SPENPRI = 1;
  	hw->CTL_B.bit.SPENSEC = 0;
  	hw->CTL_B.bit.IFS = 0; //receive channel fs is tied to transmit channel in hardware

  	hw->CTL_B.bit.OPMODE = 1;
  	hw->CTL_B.bit.LAFS = 0;
  	hw->CTL_B.bit.LSBF = 0; //MSB first data
  	hw->CTL_B.bit.CKRE = 1;
  	hw->CTL_B.bit.SLEN = wordLength - 1;

  	hw->MCTL_B.bit.MCE = 0;
}

void I2S::writeDirect(int32_t l, int32_t r)
{
	hw->TXPRI_A.reg = l;
	hw->TXPRI_A.reg = r;
}
