#ifndef TICK_HPP_
#define TICK_HPP_

#include <stdint.h>

namespace tick
{
	class Tick
	{
	public:
		Tick();
		void ResetTime();
		uint32_t ElapsedTime();
		int8_t RegisterTimer(void (*Function)(Tick *FuncArg), uint16_t Period);
		void UnregisterTimer();
		~Tick();
	private:
		int8_t CallBackIndex = -1;
		uint32_t TimeStamp = 0;
	};
}

#endif
