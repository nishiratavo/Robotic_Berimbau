#include "tick.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

using namespace tick;

static const uint8_t Slots = 6;
static volatile uint32_t GlobalTime = 0;
static volatile uint8_t TimerInitialized = 0;

struct CallBacks
{
	uint16_t Period;
	uint16_t Count;
	void (*Function)(Tick *FuncArg);
	Tick *FuncArg;
};

static volatile CallBacks RegisteredCallBacks[Slots];

void TickInit()
{
	for (uint8_t i = 0; i < Slots; i++)
	{
		RegisteredCallBacks[i].Period = 0;
	}

	TCNT0 = 0;
	OCR0A = 250;
	TIMSK0 = (1 << OCIE0A);
	TCCR0A = 0;
	TCCR0B = (1 << CS01) | (1 << CS00);
}

Tick::Tick()
{
	ResetTime();
	if (TimerInitialized == 0)
	{
		TickInit();
	}
}

void Tick::ResetTime()
{
	TimeStamp = GlobalTime;
}

uint32_t Tick::ElapsedTime()
{
	return GlobalTime - TimeStamp;
}

int8_t Tick::RegisterTimer(void (*Function)(Tick *FuncArg), uint16_t Period)
{
	uint8_t i;

	if (CallBackIndex == -1)
	{
		for (i = 0; i < Slots; i++)
		{
			if (RegisteredCallBacks[i].Period == 0)
			{
				ATOMIC_BLOCK(ATOMIC_FORCEON)
				{
					RegisteredCallBacks[i].Function = Function;
					RegisteredCallBacks[i].Count = Period;
					RegisteredCallBacks[i].Period = Period;
				}
				CallBackIndex = i;
				return 0;
			}
		}
	}
	else
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			RegisteredCallBacks[CallBackIndex].Function = Function;
			RegisteredCallBacks[CallBackIndex].Count = Period;
			RegisteredCallBacks[CallBackIndex].Period = Period;
		}
		return 0;
	}
	
	return -1;
}

void Tick::UnregisterTimer()
{
	if (CallBackIndex != -1)
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			RegisteredCallBacks[CallBackIndex].Period = 0;
		}
	}
}

Tick::~Tick()
{
	UnregisterTimer();
}

ISR(TIMER0_COMPA_vect)
{
	TIFR0 &= ~(1 << OCF0A);
	GlobalTime++;

	for (uint8_t i = 0; i < Slots; i++)
	{
		if (RegisteredCallBacks[i].Period != 0)
		{
			if (RegisteredCallBacks[i].Count == 0)
			{
				RegisteredCallBacks[i].Function(RegisteredCallBacks[i].FuncArg);
				RegisteredCallBacks[i].Count = RegisteredCallBacks[i].Period;
			}
			else RegisteredCallBacks[i].Count--;
		}
	}
}
