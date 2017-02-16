#ifndef STONE_H_
#define STONE_H_

#include "Arduino.h"
#include <Servo.h>

class Stone{
public:
	Servo myservo;
	int angle[3]= {0,90,180};
	int current_angle;
	Stone();
	//function that sets the angles for each instrument	
	void force_angle(int pos);
	void save_angle(int nota);
	void attach(int pin);
	// function that moves the stone to the correct position according to the angle vector
	void move_to_position(int nota);
	void call_function(int nota, int parametro, int angulo);
};



#endif


