
#include "Arduino.h"
#include "Stone.h"


Stone::Stone(){}
	
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

void Stone::attach(int pin){
	myservo.attach(pin);
}

void Stone::call_function(int nota, int parametro, int angulo){
	if (nota == 0){
		parametro = parametro - 60;
		move_to_position(parametro);
	}
	if (nota == 1){
		parametro = parametro -60;
		save_angle(parametro);	
	}
	if (nota == 2){
		force_angle(angulo);
	}
}

