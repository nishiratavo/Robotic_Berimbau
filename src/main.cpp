#include "servo.hpp"
#include "gpiodef.hpp"
#include "usart.hpp"
#include "tick.hpp"
#include "dcmotor.hpp"

#include <util/delay.h>

using namespace servo;
using namespace usart;
using namespace tick;
using namespace dcmotor;

static DCMotor Baqueta;

static void RXByte(uint8_t Data)
{
	switch (Data)
	{
	case 'A':
		LedM1ON();
		break;
		
	case 'B':
		LedM1OFF();		
    break;

	default:
		break;
	}
}

static void Blink(Tick *MyTick)
{
	static uint8_t status = 0;

	switch (status)
	{
	case 0:
		Baqueta.Action(TurnCW, 255);
		break;

	case 1:
		Baqueta.Action(TurnCCW, 255);
		break;

	default:
		break;
	}
	if (status < 1) status++;
	else status = 0;
}

int main()
{
	Servo rock;
	Usart serial;
	Tick BlinkLed;
	
	GpioInit();

	BlinkLed.RegisterTimer(&Blink, 400);

	rock.SetAngle(0);
	serial.Setup(9600);
	
	serial.EnableRXByteInt(&RXByte);

	while (1)
	{
		serial.WriteString("Sucesso!\n");
		rock.SetAngle(-25);
		_delay_ms(500);
		rock.SetAngle(25);
		_delay_ms(500);
	}
}
