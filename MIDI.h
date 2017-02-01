#ifndef MIDI_H_
#define MIDI_H_

#include "Arduino.h"

#define NOTEON_CH0 144
#define NOTE_DOM 60 // dom note of berimbau assigned to MIDI C4
#define NOTE_DIM 61 // dim note of berimbau assigned to MIDI C#4
#define NOTE_TIM 62 // tim note of berimbau assigned to MIDI D4

class MIDI{
public:
	MIDI(long int baud_rate);
	void receive(byte command, byte note, byte velocity);
	int decode(byte note, byte velocity);
};



#endif