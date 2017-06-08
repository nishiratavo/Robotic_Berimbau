#include "gpiodef.hpp"
#include "events.hpp"

#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
	GpioInit();
	EventsInit();
	
	while (1)
	{
		
	}
}
