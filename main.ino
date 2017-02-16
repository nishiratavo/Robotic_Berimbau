#include "MIDI.h"
#include "Stone.h"

byte command;
byte note;
byte velocity;
int *parameter;
int *angle;
int pin = 12;

MIDI midi;
Stone mystone;

void setup() {
  Serial.begin(31250);
  mystone.attach(12);
  // put your setup code here, to run once:
  //pinMode(13,OUTPUT);
  //digitalWrite(13,LOW);
}	

void loop() {
  int nota;
  // put your main code here, to run repeatedly:
  if(midi.receive(&command, &note, &velocity)) {
    nota = midi.decode(command, note, velocity, parameter, angle); 
  
	  mystone.call_function(nota, *parameter, *angle);
	  command = 0;
	  note = 0;
	  velocity = 0;
  }
}
