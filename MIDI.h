#ifndef MIDI_H_
#define MIDI_H_

#include <Arduino.h>

#define NOTEON_CH0 144
#define NOTE_DOM 60 // dom note of berimbau assigned to MIDI C4
#define NOTE_DIM 61 // dim note of berimbau assigned to MIDI C#4
#define NOTE_TIM 62 // tim note of berimbau assigned to MIDI D4
#define CONTROL_CHANGE 176 // Control signal
#define CONTROL_0 0 // Controller 0
#define CONTROL_1 1 // Controller 1
#define CONTROL_2 2 // Controller 2
#define CONTROL_3 3 // Controller 3

class MIDI{
public:
	MIDI();
	int receive(byte *command, byte *note, byte *velocity);
	int decode(byte command, byte note, byte velocity, int *parameter, int *angle);
};



#endif
