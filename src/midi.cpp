#include "midi.hpp"
#include <stddef.h>

using namespace midi;

static const uint8_t MidiSlots = 9;
static void (*MidiCalls[MidiSlots])(uint8_t Arg1, uint8_t Arg2);
static uint8_t MidiChannel = 0;

static constexpr uint8_t EventTable[] = {0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};

static void MidiReceive(uint8_t Data)
{
	static uint8_t MsgState = 0;
	static uint8_t Channel = 0xFF, Arg1 = 0, Arg2 = 0;
	static MidiEvent Slot = NoteOFF;

	switch (MsgState)
	{
	case 0:
	{
		Channel = Data & 0x0F;
		switch (Data & 0xF0)
		{
		case EventTable[NoteOFF]:
			Slot = NoteOFF;
			MsgState = 1;
			break;

		case EventTable[NoteON]:
			Slot = NoteON;
			MsgState = 1;
			break;

		case EventTable[ContinuousCtrl]:
			Slot = ContinuousCtrl;
			MsgState = 1;
			break;

		case EventTable[PitchBend]:
			Slot = PitchBend;
			MsgState = 1;
			break;
			
		default:
			MsgState = 0;
			break;
		}
		break;
	}

	case 1:
		Arg1 = Data;
		MsgState = 2;
		break;

	case 2:
		Arg2 = Data;

		//if (Channel == MidiChannel)
		//{
			if (MidiCalls[Slot] != NULL)
			{
				MidiCalls[Slot](Arg1, Arg2);
			}
		//}

		MsgState = 0;
		break;

	default:
		break;
	}
}


Midi::Midi()
{
	for (uint8_t i = 0; i < MidiSlots; i++)
	{
		MidiCalls[i] = NULL;
	}
	
	MidiPort.Setup(31250);
	MidiPort.EnableRXByteInt(&MidiReceive);
}

void Midi::AttachEvent(MidiEvent Event, void (*func)(uint8_t Arg1, uint8_t Arg2))
{
	MidiCalls[Event] = func;
}

void Midi::Setup(uint8_t Channel)
{
	MidiChannel = Channel;
}

Midi::~Midi()
{
	
}
