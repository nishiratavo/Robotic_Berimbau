#ifndef GPIODEF_HPP_
#define GPIODEF_HPP_

#include <stdint.h>
#include <avr/io.h>

void GpioInit();
uint8_t ReadDIPSwitch();

/*
 * Inline Functions
 */

static inline void LedM1ON()
{
	PORTC |= (1 << 0);
}

static inline void LedM1OFF()
{
	PORTC &= ~(1 << 0);
}

static inline void LedM2ON()
{
	PORTC |= (1 << 1);
}

static inline void LedM2OFF()
{
	PORTC &= ~(1 << 1);
}

static inline void LedMIDION()
{
	PORTC |= (1 << 2);
}

static inline void LedMIDIOFF()
{
	PORTC &= ~(1 << 2);
}

static inline void LedNearStingON()
{
	PORTC |= (1 << 3);
}

static inline void LedNearStingOFF()
{
	PORTC &= ~(1 << 3);
}

static inline void LedSensorNearON()
{
	PORTC |= (1 << 4);
}

static inline void LedSensorNearOFF()
{
	PORTC &= ~(1 << 4);
}

static inline void LedSensorFarON()
{
	PORTC |= (1 << 5);
}

static inline void LedSensorFarOFF()
{
	PORTC &= ~(1 << 5);
}

static inline void M1ON()
{
	PORTB |= (1 << 4);
}

static inline void M1OFF()
{
	PORTB &= ~(1 << 4);
}

static inline void M2ON()
{
	PORTB |= (1 << 5);
}

static inline void M2OFF()
{
	PORTB &= ~(1 << 5);
}
#endif
