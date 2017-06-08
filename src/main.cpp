#include "servo.hpp"
#include "gpiodef.hpp"
#include "usart.hpp"
#include "dcmotor.hpp"
#include "midi.hpp"

#include <util/delay.h>
#include <avr/interrupt.h>

using namespace servo;
using namespace usart;
using namespace dcmotor;
using namespace midi;

enum MotorPos
{
	EndPos,
	Middle,
	NearString
};

enum Sensors
{
	NearStringSen,
	FarStringSen,
};

static DCMotor Baqueta;
static Midi MidiInterface;
static Servo Rock;
static volatile MotorPos StickPos = EndPos;
static volatile Sensors LastSensor = NearStringSen;

/*
 * NearSensor interrupt routine
 */
ISR(INT0_vect)
{
	if (isNearSensorON())
	{
		LedSensorNearOFF();

		/*
		 * If the drumstick is returning to the home position, turn on
		 * the motor in the CW direction (accelerates towards the home
		 * position)
		 */
		if (StickPos == NearString)
		{
			StickPos = Middle;
			LedNearStringOFF();
			Baqueta.Action(TurnCW, 120, 800);
		}
		else
		{
			Baqueta.Action(OFF, 0);
			LedNearStringON();
			StickPos = NearString;
		}

		LastSensor = NearStringSen;
	}
	else LedSensorNearON();
}

/*
 * FarSensor interrupt routine
 */
ISR(INT1_vect)
{
	if (isFarSensorON())
	{
		LedSensorFarOFF();
		/*
		 * If the drumstick is returning from a previous played note,
		 * lock it in the home position with a timeout of 400ms to
		 * avoid it turn in the CCW direction
		 */
		if (StickPos == Middle && LastSensor == NearStringSen)
		{
			StickPos = EndPos;
			Baqueta.Action(TurnCW, 160, 400);
		}
		else
		{
			StickPos = Middle;
		}

		LastSensor = FarStringSen;
	}
	else LedSensorFarON();
}

static void MidiNoteON(uint8_t Arg1, uint8_t Arg2)
{
	if (Arg2 != 0)
	{
		LedMIDION();
		Baqueta.Action(TurnCCW, 2*Arg2);
		LedM2OFF();
	}
	else LedMIDIOFF();
}

static void MidiNoteOFF(uint8_t Arg1, uint8_t Arg2)
{
	LedMIDIOFF();
}

static void MidiRockCtrl(uint8_t Arg1, uint8_t Arg2)
{
	static uint8_t RockState = 0;

	switch (Arg1)
	{
	case 0:
		Rock.SetAngle(-10);
		RockState = 0;
		break;

	case 1:
		if (RockState == 0)
		{
			Rock.SetAngle(15);
		}
		else if (RockState == 2)
		{
			Rock.SetAngle(14);
		}

		RockState = 1;
		break;

	case 2:
		Rock.SetAngle(27);
		RockState = 2;
		break;

	default:
		break;
 	}
 }

int main()
{
	Usart serial;

	GpioInit();

	Rock.SetAngle(30);
	_delay_ms(200);
	Rock.SetAngle(0);

	Baqueta.Action(TurnCW, 255);
	_delay_ms(100);
	Baqueta.Action(Brake, 255);

	StickPos = EndPos;

	EICRA = (1 << ISC00) | (0 << ISC00) |
		(1 << ISC10) | (0 << ISC10);
	EIMSK = (1 << INT0) | (1 << INT1);
	EIFR = 0;
	sei();

	MidiInterface.SetChannelCall(&ReadDIPSwitch);
	MidiInterface.AttachEvent(NoteON, &MidiNoteON);
	MidiInterface.AttachEvent(NoteOFF, &MidiNoteOFF);
	MidiInterface.AttachEvent(PitchBend, &MidiRockCtrl);

	while (1)
	{

	}
}
