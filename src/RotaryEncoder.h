#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

class RotaryEncoder {
	private:
		uint8_t DT;  
		uint8_t CLK;  

		bool currentStateCLK;
		bool lastStateCLK;

		int value;
		bool updated;

		int min;
		int max;
		bool loop;
	public:
		RotaryEncoder(uint8_t _dt, uint8_t _clk, int _min, int _max, int _actual, bool _loop);
		void Process();
		uint8_t GetPinDT();
		uint8_t GetPinCLK();
		bool Updated();
		int Value();
};

#endif
