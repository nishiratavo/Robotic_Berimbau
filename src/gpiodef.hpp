#ifndef GPIODEF_HPP_
#define GPIODEF_HPP_

#include <stdint.h>
#include <avr/io.h>

void GpioInit();
uint8_t ReadDIPSwitch();

/*
 * Inline Functions
 */

static inline int8_t isNearSensorON()
{
	return ((PIND & (1 << 2)) != 0);
}

static inline int8_t isFarSensorON()
{
	return ((PIND & (1 << 3)) != 0);
}

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

static inline void LedNearStringON()
{
	PORTC |= (1 << 3);
}

static inline void LedNearStringOFF()
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
  LedM1ON();
}

static inline void M1OFF()
{
	PORTB &= ~(1 << 4);
  LedM1OFF();
}

static inline void M2ON()
{
	PORTB |= (1 << 5);
  LedM2ON();
}

static inline void M2OFF()
{
	PORTB &= ~(1 << 5);
  LedM2OFF();
}
#endif
