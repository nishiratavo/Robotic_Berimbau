#include "MIDI.h"
#include "Arduino.h"

MIDI::MIDI()
{
}

int MIDI::receive(byte *command, byte *note, byte *velocity)
{
	if(Serial.available())
	{
		*command = Serial.read();
    //Serial.write(*command);
    if ( ((*command) == 144) || ((*command)==176) ) {
      //digitalWrite(13,HIGH);
      while (!Serial.available());
  		*note = Serial.read();
      //Serial.write(*note);
      while (!Serial.available());
  		*velocity = Serial.read();
      //Serial.write(*velocity);
      return 1;
    }
	}
  return 0;
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

	if ((command == CONTROL_CHANGE) && (note != 0))
	{
		switch(note)
		{

			case CONTROL_1 :
				*parameter = NOTE_DOM;
         //digitalWrite(13,HIGH);
				break;

			case CONTROL_2 :
				*parameter = NOTE_DIM;
				break;

			case CONTROL_3 :
				*parameter = NOTE_TIM;
				break;

			default :
        break;

		}
    //digitalWrite(13,HIGH);
		return 1;
	}
	if ((command == 176) && (note == 0))
	{
		*angle = velocity;
		return 2;
	}
	
}

