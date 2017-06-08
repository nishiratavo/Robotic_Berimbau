#include "gpiodef.hpp"
#include "events.hpp"
#include "statemachine.hpp"

#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
	StateMachine StickCtrl;

	GpioInit();
	EventsInit();



	while (1)
	{
  if (isNearSensorON()) { LedSensorNearON();}
  else {LedSensorNearOFF();}

  if (isFarSensorON()) { LedSensorFarON();}
  else {LedSensorFarOFF();}





    StickCtrl.operate();
	}
}
