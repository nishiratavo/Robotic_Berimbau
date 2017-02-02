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

int MIDI::decode(byte command, byte note, byte velocity, int *parameter, int *angle) // parameter for stick() and stone()
{	
	if (command == NOTEON_CH0)
	{
		switch(note)
		{
			case NOTE_DOM : // run stick()
				*parameter = NOTE_DOM;
			break;

			case NOTE_DIM : // run stick and stone() / stone full strength
				*parameter = NOTE_DIM;
			break;

			case NOTE_TIM : // run stick and stone() / stone half strength
				*parameter = NOTE_TIM;
			break;
		}
		return 0;
	}

	if (command == CONTROL_CHANGE)
	{
		switch(note)
		{

			case CONTROL_1 :
				*parameter = NOTE_DOM;
				break;

			case CONTROL_2 :
				*parameter = NOTE_DIM;
				break;

			case CONTROL_3 :
				*parameter = NOTE_TIM;
				break;

			default :

		}
		return 1;
	}
	if (command == CONTROL_CHANGE && note == CONTROL_0)
	{
		*angle = velocity;
		return 2;
	}
	
}

