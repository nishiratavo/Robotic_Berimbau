#include "gpiodef.hpp"

void GpioInit()
{
	/*
	 * Configure the PC0 - PC5
	 * GPIOs as outputs
	 */
	DDRC |= 0b00111111;

	/*
	 * Configure the PD4 - PD7
	 * GPIOs as inputs and enable
	 * the internal pullups
	 */
	DDRD &= 0b00000011;
	PORTD |= 0b11111100;

	/*
	 * Configure the PB4 and PB5
	 * GPIOs as outputs
	 */
	DDRB |= 0b00110000;
	PORTB &= 0b11001111;
}

/*
 * Returns the value seted by the
 * DIP Switch
 */
uint8_t ReadDIPSwitch()
{
	uint8_t Status = 0;
	if (PIND & (1 << 4)) Status |= 8;
	if (PIND & (1 << 5)) Status |= 4;
	if (PIND & (1 << 6)) Status |= 2;
	if (PIND & (1 << 7)) Status |= 1;
	return Status;
}
