#ifndef _LIB_I2S_H
#define _LIB_I2S_H

#include <bf706_device.h>
#include <dma.h>

class I2S
{
  public:
    I2S(Sportgroup *sport, uint8_t _pinCLK, uint8_t _pinFS, uint8_t _pinAD0, uint8_t _pinBD0);
    bool begin(uint32_t clkRate, uint32_t fsRate, uint8_t wordLength);
    void beginDMAAutobuffer(uint32_t addr, uint32_t count, bool tx = true);

    void beginDMAPassThrough(uint32_t addrPing, uint32_t addrPong, uint32_t count,
    		PDMADescriptor *pingTx, PDMADescriptor *pingRx,
    		PDMADescriptor *pongTx, PDMADescriptor *pongRx);

    void writeDirect(int32_t l, int32_t r);

  protected:
    Sportgroup *hw;

  private:
    uint8_t _ucPinCLK, _ucPinFS, _ucPinAD0, _ucPinBD0;
};

#endif
