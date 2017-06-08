#include "dcmotor.hpp"
#include "gpiodef.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

using namespace dcmotor;

static volatile uint32_t MotorPeriod = 0;

/*
 * Interrupt routine of the Timer2 (Overflow), used to turn off the DC
 * motor once the timeout has reached
 */
ISR(TIMER2_OVF_vect)
{
	if (MotorPeriod > 0)
	{
		MotorPeriod--;
		if (MotorPeriod == 0)
		{
			
			OCR2A = 255;
			M2OFF();
			M1OFF();
		}
	}
}

DCMotor::DCMotor()
{
	/*
	 * Configure PB3 pin as an output (PWM)
	 */
	DDRB |= (1 << 3);
	
	OCR2A = 0;

	/*
	 * Configure the Timer2 to mode 2 (Fast PWM)
	 */
	TCCR2A = (1 << COM2A1) | (1 << WGM21) |
		(1 << WGM20);

	/*
	 * Configure the PWM frequency to 62.5KHz (Timer2 Clock = 16MHz,
	 * PWM Clock = (Timer Clock) / 256)
	 */
	TCCR2B = (0 << CS22) | (0 << CS21) |
		(1 << CS20);

	/*
	 * Enable the Overflow Interrupt of the Timer2
	 */
	TIMSK2 = TOIE2;
}

void DCMotor::Action(MotorAction Act, uint8_t Power, int16_t TimeOut)
{
	/*
	 * Disables the Timer2 overflow interrupt temporally
	 */
	TIMSK2 &= ~TOIE2;

	/*
	 * Clear the Timer2 counter to make the timeout accurate
	 */
	TCNT2 = 0;

	/*
	 * If the specified timeout is negative, set MotorPeriod to 0, so
	 * the effective timeout is infinite
	 */
	if (TimeOut < 0)
	{
		MotorPeriod = 0;
	}
	/*
	 * If the specified timeout is 0, turn off the motor
	 */
	else if (TimeOut == 0)
	{
		M2OFF();
		M1OFF();
		OCR2A = 255;
		return;
	}
	/*
	 * For positive values of the timeout, calculate the equivalent
	 * number of interrupt events of the Timer2 (TimeOut in ms):
	 * MotorPeriod = (62500Hz/1000Hz) * TimeOut
	 */
	else
	{
		MotorPeriod = (TimeOut * 62) + (TimeOut >> 2);
	}

	/*
	 * Execute the solicited action
	 */
	switch (Act)
	{
	case TurnCCW:
		M2OFF();
		M1ON();
		OCR2A = Power;
		break;

	case TurnCW:
		M1OFF();
		M2ON();
		OCR2A = Power;
		break;

	case OFF:
		M2OFF();
		M1OFF();
		OCR2A = 0;
		break;

	case Brake:
		M2OFF();
		M1OFF();
		OCR2A = Power;
		break;

	default:
		break;
	}

	/*
	 * Reenable the Timer2 overflow interrupt
	 */
	TIMSK2 |= TOIE2;
}

void DCMotor::Action(MotorAction Act, uint8_t Power)
{
	/*
	 * If the timeout parameter is ommited, assume an infinite timeout
	 */
	Action(Act, Power, -1);
}

DCMotor::~DCMotor()
{
	/*
	 * Disable the Timer2 and turn off the motor
	 */
	TCCR2A = 0;
	TCCR2B = 0;
	TIMSK2 = 0;
	M2OFF();
	M1OFF();
}
