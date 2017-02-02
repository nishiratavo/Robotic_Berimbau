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








	int state = 0;
	if (command == NOTEON_CH0)
	{
		state = 1; // Play note
	}
	else if (command == CONTROL_CHANGE)
	{
		state = 2; // calibration
	}
	if (state == 1)
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
	if (state == 2)
	{
		if (note == CONTROL_0)
		{
			state = 3; // 
		}
		else if(note == CONTROL_1)
		{
			state = 4;
		}
	}
	if (state == 3)
	{
		*parameter = velocity;
	}
	if (state == 4)
	{
		
	}
	
}

