#include <MIDI.h>

byte command;
byte note;
byte velocity;

MIDI midi(57600);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  midi.receive(command, note, velocity);
  midi.decode(note, velocity);
  //stone()
  //stick()
  

}
