/*
 * timer.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: Dean
 */


#include "Timer.h"
#include "wiring_private.h"

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

Timer::Timer(uint8_t pin)
{
	_pin = pin;
	int tmr = g_APinDescription[pin].ulTimer;
	_tmr = tmr;
}

bool Timer::begin( uint32_t freq )
{
	if(_tmr != NOT_ON_TIMER){
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

void Timer::setDutyCycle( float duty )
{
	setWid(getPer() * duty);
}

void Timer::setFrequency( uint32_t freq )
{
	setPer(VARIANT_SCLK0 / freq);
}
