
#include "Arduino.h"
#include "Stone.h"


Stone::Stone();
	
void Stone::force_angle(int pos){
	myservo.write(pos);
	current_angle = pos;
}

void Stone::save_angle(int nota){
	angle[nota] = current_angle;
}

void Stone::move_to_position(int nota){
	force_angle(angle[nota]);
}


