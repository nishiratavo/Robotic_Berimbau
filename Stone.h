#ifndef STONE_H_
#define STONE_H_

#include "Arduino.h"
#include <Servo.h>

class Stone{
public:
	Servo myservo;
	int angle[3]= {0,0,0};
	int current_angle;
	void.attach(int pin);
	Stone();
	//function that sets the angles for each instrument	
	void force_angle(int pos);
	void save_angle(int nota);
	// function that moves the stone to the correct position according to the angle vector
	void move_to_position(int nota);
};



#endif


