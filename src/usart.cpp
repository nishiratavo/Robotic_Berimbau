#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart.hpp"

using namespace usart;

static void (*RX_INT)(uint8_t Data);

Usart::Usart()
{
	/*
	 * Configure the PD0 pin (RXD) as
	 * an input and the PD1 pin (TXD) as
	 * an output
	 */
	DDRD |= 0x02;
	DDRD &= ~0x01;
}

void Usart::Setup(uint32_t BaudRate)
{
	Setup(BaudRate, 1, None);
}

void Usart::Setup(uint32_t BaudRate, uint8_t StopBits,
				  Parity Par)
{
	uint8_t UCSR0C_tmp = 0;
	uint32_t BAUD_tmp;

	switch (Par)
	{
	case Odd:
		UCSR0C_tmp |= (1 << UPM01) | (1 << UPM00);
		break;

	case Even:
		UCSR0C_tmp |= (1 << UPM01) | (0 << UPM00);
		break;

	case None:
    break;

	default:
		break;
	}

	switch (StopBits)
	{
	case 1:
		break;

	case 2:
		UCSR0C_tmp |= USBS0;
		break;

	default:
		break;
	}

	UCSR0C = UCSR0C_tmp | (1 << UCSZ01) | (1 << UCSZ00);

	UCSR0A = (1 << U2X0);

	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	BAUD_tmp = (F_CPU / 8);
	BAUD_tmp /= BaudRate;
	UBRR0 = BAUD_tmp - 1;
}

void Usart::WriteString(const char *Str)
{
	while (*Str != 0)
	{
		while((UCSR0A & (1 << UDRE0)) == 0);
		UDR0 = *Str++;
	}
}

void Usart::WriteByte(uint8_t Data)
{
	while((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = Data;
}

uint8_t Usart::ReadByte()
{
	while((UCSR0A & (1 << RXC0)) == 0);
    return UDR0;
}

void Usart::EnableRXByteInt(void (*func)(uint8_t Data))
{
	RX_INT = func;
	UCSR0B &= ~(1 << RXEN0);
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0);
}

Usart::~Usart()
{
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
}

ISR(USART_RX_vect)
{
	RX_INT(UDR0);
}
