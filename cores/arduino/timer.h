/*
 * timer.h
 *
 *  Created on: Dec 10, 2017
 *      Author: Dean
 */

#ifndef BFIN_CORES_ARDUINO_TIMER_H_
#define BFIN_CORES_ARDUINO_TIMER_H_

#include <Arduino.h>

enum {
	TIMER_CFG_TMODE_IDLE = 0,
	TIMER_CFG_TMODE_PERIOD_WATCHDOG = 8,
	TIMER_CFG_TMODE_WIDTH_WATCHDOG,
	TIMER_CFG_TMODE_MEAS_REPORT_RISING,
	TIMER_CFG_TMODE_MEAS_REPORT_FALLING,
	TIMER_CFG_TMODE_CONTINUOUS_PWM,
	TIMER_CFG_TMODE_SINGLE_PWM,
	TIMER_CFG_TMODE_EXTCLK,
	TIMER_CFG_PININT,
};

#define TIMER_NO_PIN -1

class Timer {
public:
	Timer(int pin = TIMER_NO_PIN);

	bool begin( uint32_t freq );

	void enable( void );
	void disable( void );
	void clearInterrupt( void );

	void setDutyCycle( float duty );
	void setFrequency( uint32_t freq );

private:
	int8_t _tmr, _pin;
	inline void setCfg(uint32_t cfg);
	inline void setWid(uint32_t wid);
	inline void setPer(uint32_t per);

	inline uint32_t getPer( void );
};


#endif /* BFIN_CORES_ARDUINO_TIMER_H_ */
