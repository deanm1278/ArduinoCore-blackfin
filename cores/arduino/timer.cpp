/*
 * timer.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: Dean
 */


#include "timer.h"
#include "wiring_private.h"

static uint16_t usedTimers = 0;

inline void Timer::setCfg(uint32_t cfg)
{
	*(volatile uint32_t *)(((uint32_t)&TIMER0->TMR0_CFG) + (_tmr << 5)) = cfg;
}

inline void Timer::setWid(uint32_t wid)
{
	*(volatile uint32_t *)(((uint32_t)&TIMER0->TMR0_WID) + (_tmr << 5)) = wid;
}

inline void Timer::setPer(uint32_t per)
{
	*(volatile uint32_t *)(((uint32_t)&TIMER0->TMR0_PER) + (_tmr << 5)) = per;
}

inline uint32_t Timer::getPer( void )
{
	return *(volatile uint32_t *)(((uint32_t)&TIMER0->TMR0_PER) + (_tmr << 5));
}

Timer::Timer(int pin)
{
	_pin = pin;
	_tmr = -1;
	if(pin > TIMER_NO_PIN){
		int tmr = g_APinDescription[pin].ulTimer;
		_tmr = tmr;
		usedTimers |= (1<<_tmr);
	}
	else {
		//find an unused timer
		for(int i=TIMER_0; i<TIMER_4; i++){
			if(!(usedTimers & (1<<i))){
				_tmr = i;
				usedTimers |= (i<<_tmr);
				break;
			}
		}
	}
}

bool Timer::begin( uint32_t freq )
{
	if(_tmr != TIMER_NO_PIN){
		setCfg(TIMER_CFG_TMODE_CONTINUOUS_PWM | (0x3 << 4));
		setFrequency(freq);
		setDutyCycle(.5);

		pinPeripheral(_pin, PIO_MUX_1);
		enable();
		return true;
	}
	return false;
}

void Timer::enable( void )
{
	TIMER0->RUN_SET.reg = (1 << _tmr);
}

void Timer::disable( void )
{
	TIMER0->RUN_CLR.reg = (1 << _tmr);
}

void Timer::clearInterrupt( void )
{

}

void Timer::setDutyCycle( float duty )
{
	setWid(getPer() * duty);
}

void Timer::setFrequency( uint32_t freq )
{
	setPer(VARIANT_SCLK0 / freq);
}
