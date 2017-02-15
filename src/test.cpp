#include "test.hpp"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

LedBlink::LedBlink(int delay)
{
	DDRB = 0xFF;
	_delay = delay;
}

void LedBlink::Blink()
{
	while(1)
	{
		PORTB ^= 0xFF;
		for (int del = _delay; del > 0; del--) {
			_delay_ms(1);
		}
	}
}
