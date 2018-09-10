#include "UART.h"
#include "Arduino.h"
#include "wiring_private.h"

Uart::Uart(Uartgroup *uart, uint8_t _pinRX, uint8_t _pinTX)
{
  hw = uart;
  uc_pinRX = _pinRX;
  uc_pinTX = _pinTX;
}

void Uart::begin(unsigned long baudrate)
{
  begin(baudrate, SERIAL_8N1);
}

void Uart::begin(unsigned long baudrate, uint16_t config)
{
  (void) config;
  //TODO: other configs
  pinPeripheral(uc_pinRX, g_APinDescription[uc_pinRX].ulPinType);
  pinPeripheral(uc_pinTX, g_APinDescription[uc_pinTX].ulPinType);

  //set baud rate = SCLK0/ (16^(1 - CLK.EDBO) * CLK.DIV)
  hw->CLK.bit.DIV = VARIANT_SCLK0 / (16 * baudrate);

  //hw->CLK.bit.EDBO = 1;
  //hw->CLK.bit.DIV = VARIANT_SCLK0 / baudrate;

  //no parity bits
  hw->CTL.bit.PEN = 0;

  //1 stop bit
  hw->CTL.bit.STB = 0;

  //UART mode
  hw->CTL.bit.MOD = 0;

  //8 bit word
  hw->CTL.bit.WLS = 0x03;

  //enable rx interrupt
  //without DMA channels for now
  hw->IMSK_SET.bit.ELSI = 1;
  hw->IMSK_SET.bit.ERBFI = 1;
  hw->IMSK_SET.bit.ERXS = 1;

  if(hw == UART0){
	setIRQPriority(48, IRQ_MAX_PRIORITY >> 1);
	enableIRQ(48);
  }
  else if(hw == UART1){
	  setIRQPriority(51, IRQ_MAX_PRIORITY >> 1);
	  enableIRQ(51);
  }
  else{
  	//fail
  	while(1);
  }

  //enable
  hw->CTL.bit.EN = 1;
}

void Uart::end()
{
  rxBuffer.clear();
}

void Uart::flush()
{
  
}

void Uart::IrqHandler()
{
	uint8_t val = hw->RBR.bit.VALUE;
	rxBuffer.store_char(val);
}

int Uart::available()
{
  return rxBuffer.available();
}

int Uart::availableForWrite()
{
  return hw->STAT.bit.THRE;
}

int Uart::peek()
{
  return rxBuffer.peek();
}

int Uart::read()
{
  return rxBuffer.read_char();
}

size_t Uart::write(const uint8_t data)
{
  while(!hw->STAT.bit.THRE);
  hw->THR.reg = data;
  return 1;
}
