#ifndef USART_HPP_
#define USART_HPP_

#include <inttypes.h>

namespace usart
{	
	typedef enum
	{
		Odd,
		Even,
		None,
	} Parity;

	class Usart
	{
	public:
		Usart();
		void Setup(uint32_t BaudRate);
		void Setup(uint32_t BaudRate, uint8_t StopBits,
				   Parity Par);
		uint8_t ReadByte();
		void WriteByte(uint8_t Data);
		void WriteString(const char *Str);
		void EnableRXByteInt(void (*func)(uint8_t Data));
		~Usart();
	private:
		void DefaultInt();
		void (*ByteReceived) (uint8_t Data) ;
		void (*ByteWritten) ();
	};

}
#endif
