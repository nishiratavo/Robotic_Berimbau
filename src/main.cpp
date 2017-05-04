#include "servo.hpp"
#include "gpiodef.hpp"
#include "usart.hpp"
#include "tick.hpp"
#include "dcmotor.hpp"
#include "midi.hpp"

#include <util/delay.h>
#include <avr/interrupt.h>

using namespace servo;
using namespace usart;
using namespace tick;
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
static volatile Tick MotorTime;
static Midi MidiInterface;
static Tick HitTimer;
static Servo Rock;
static volatile MotorPos StickPos = EndPos;
static volatile Sensors LastSensor = NearStringSen;

ISR(INT0_vect)
{
	if (isNearSensorON())
	{
		LedSensorNearOFF();
		if (StickPos == NearString)
		{
			StickPos = Middle;
			LedNearStringOFF();
			Baqueta.Action(TurnCW, 120);
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

ISR(INT1_vect)
{
	if (isFarSensorON())
	{
		LedSensorFarOFF();
		if (StickPos == Middle && LastSensor == NearStringSen)
		{
			StickPos = EndPos;
			Baqueta.Action(Break, 0);
		}
		else
		{
			//Baqueta.Action(Break, 0);
			StickPos = Middle;
		}

		LastSensor = FarStringSen;
	}
	else LedSensorFarON();
}

// static void HitString(Tick *MyTick)
// {
// 	static uint8_t status = 0;

// 	switch (status)
// 	{
// 	case 0:
// 	case 1:
// 		Baqueta.Action(TurnCCW, 255);
// 		status++;
// 		break;

// 	case 2:
// 		Baqueta.Action(OFF, 255);
// 		status++;
// 		break;
		
// 	case 3:
// 		Baqueta.Action(TurnCW, 160);
// 		status++;
// 		break;
		
// 	case 4:
// 		Baqueta.Action(Break, 255);
// 		MyTick->UnregisterTimer();
// 		status = 0;
// 		break;

// 	default:
// 			break;
// 	}
// 	MyTick->UnregisterTimer();
// 	// if (status < 4) status++;
// 	// else status = 0;
// }

static void MidiNoteON(uint8_t Arg1, uint8_t Arg2)
{
	if (Arg2 != 0)
	{
		LedMIDION();
		Baqueta.Action(TurnCCW, 2*Arg2);
		HitTimer.ResetTime();
		LedM2OFF();
		//HitTimer.RegisterTimer(&HitString, 50);
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
	Tick BlinkLed;
	
	GpioInit();

	Rock.SetAngle(30);
	_delay_ms(200);
	Rock.SetAngle(0);

	Baqueta.Action(TurnCW, 255);
	_delay_ms(100);
	Baqueta.Action(Break, 255);

	StickPos = EndPos;

	EICRA = (1 << ISC00) | (0 << ISC00) |
		(1 << ISC10) | (0 << ISC10);
	EIMSK = (1 << INT0) | (1 << INT1);
	EIFR = 0;
	sei();
	
	//BlinkLed.RegisterTimer(&Blink, 100);
	MidiInterface.Setup(0);
	MidiInterface.AttachEvent(NoteON, &MidiNoteON);
	MidiInterface.AttachEvent(NoteOFF, &MidiNoteOFF);
	MidiInterface.AttachEvent(PitchBend, &MidiRockCtrl);
	
	while (1)
	{
		if (HitTimer.ElapsedTime() == 1000)
		{
			LedM2ON();
			//Baqueta.Action(TurnCW, 180);
		}
		else if (HitTimer.ElapsedTime() == 1100)
		{
			Baqueta.Action(OFF, 0);
		}
	}
}
