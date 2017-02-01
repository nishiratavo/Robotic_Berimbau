#include "MIDI.h"
#include "Arduino.h"

MIDI::MIDI(long int baud_rate)
{
	Serial.begin(baud_rate);
}

void MIDI::receive(byte command, byte note, byte velocity)
{
	if(Serial.available())
	{
		command = Serial.read();
		note = Serial.read();
		velocity = Serial.read();
	}

}

int MIDI::decode(byte note, byte velocity) // parameter for stick() and stone()
{
	switch(note)
	{
		case NOTE_DOM : // run stick()
			return 1;
		break;

		case NOTE_DIM : // run stick and stone() / stone full strength
			return 2;
		break;

		case NOTE_TIM : // run stick and stone() / stone half strength
			return 3;
		break;

		default :
			return 0;
	}
}