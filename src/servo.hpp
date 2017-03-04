/*
 * Description
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <inttypes.h>

namespace servo
{
	class Servo
	{
	public:
		Servo(int8_t Degree = 0);
		void SetAngle(int8_t Degree);
		int8_t GetAngle();
		void SetPeriods(uint16_t Min, uint16_t Max);
		~Servo();
	private:
		int8_t CurrentDegree;
		uint16_t MaxPeriod = 5000;
		uint16_t MinPeriod = 2000;
	};
}

#endif
