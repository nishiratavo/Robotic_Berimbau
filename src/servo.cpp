#include <avr/io.h>

#include "servo.hpp"

using namespace servo;

Servo::Servo(int8_t Degree)
{
	DDRB |= (1 << 1);
	TCCR1A = (1 << COM1A1) | (0 << COM1A0) |
		(1 << WGM11) | (0 << WGM10);
	TCCR1B = (1 << CS11) | (1 << WGM13) |
		(1 << WGM12);
	ICR1 = 39999;
	
	CurrentDegree = Degree;
	SetAngle(CurrentDegree);
}

void Servo::SetPeriods(uint16_t Min, uint16_t Max)
{
	MinPeriod = Min;
	MaxPeriod = Max;
}

void Servo::SetAngle(int8_t Degree)
{
	uint32_t tmp;

	tmp = Degree + 90;
	tmp *= (MaxPeriod - MinPeriod);
	tmp /= 180;
	tmp += MinPeriod;
	
	OCR1A = tmp;
	
	CurrentDegree = Degree;
}

int8_t Servo::GetAngle()
{
	return CurrentDegree;
}

Servo::~Servo()
{
	TCCR1A = 0;
	TCCR1B = 0;
}
