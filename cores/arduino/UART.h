#ifndef _UART_H
#define _UART_H

#include "HardwareSerial.h"
#include "bf706_device.h"
#include "RingBuffer.h"

#include <cstddef>

class Uart : public HardwareSerial
{
  public:
    Uart(Uartgroup *uart, uint8_t _pinRX, uint8_t _pinTX);
    void begin(unsigned long baudRate);
    void begin(unsigned long baudrate, uint16_t config);
    void end();
    int available();
    int availableForWrite();
    int peek();
    int read();
    void flush();
    size_t write(const uint8_t data);
    using Print::write; // pull in write(str) and write(buf, size) from Print

    void IrqHandler();

    operator bool() { return true; }

  private:
    Uartgroup *hw;
    RingBuffer<uint8_t> rxBuffer;

    uint8_t uc_pinRX;
    uint8_t uc_pinTX;

/* TODO: these
    SercomNumberStopBit extractNbStopBit(uint16_t config);
    SercomUartCharSize extractCharSize(uint16_t config);
    SercomParityMode extractParity(uint16_t config);
    */
};

#endif
