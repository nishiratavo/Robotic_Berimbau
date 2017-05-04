/*
 * Description
 */

#ifndef MIDI_HPP_
#define MIDI_HPP_

#include <stdint.h>
#include "usart.hpp"

namespace midi
{
	enum MidiEvent
	{
		NoteOFF = 0,
		NoteON,
		Aftertouch,
		ContinuousCtrl,
		PatchChange,
		ChannelPressure,
		PitchBend,
		SysMsg
	};
	
	class Midi
	{
	public:
		Midi();
		void Setup(uint8_t Channel);
		void AttachEvent(MidiEvent Event, void (*func)(uint8_t Arg1, uint8_t Arg2));
		~Midi();
	private:
		usart::Usart MidiPort;
	};
}

#endif
