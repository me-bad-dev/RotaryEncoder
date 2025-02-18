#include "RotaryEncoder.h"
#include <Arduino.h>

// Encoder 
RotaryEncoder::RotaryEncoder(uint8_t _dt, uint8_t _clk) {
    DT = _dt;
	CLK = _clk;

    pinMode(CLK, INPUT_PULLDOWN);
    pinMode(DT,  INPUT_PULLDOWN);
}

RotaryEncoder::RotaryEncoder(uint8_t _dt, uint8_t _clk, int _min, int _max, int _actual, bool _loop) {
	DT = _dt;
    CLK = _clk;

    advconfig = true;

    min = _min;
    max = _max;
    loop = _loop;

    value = _actual;

    pinMode(CLK, INPUT_PULLDOWN);
    pinMode(DT,  INPUT_PULLDOWN);
}


uint8_t RotaryEncoder::GetPinDT() {
	return DT;
};

uint8_t RotaryEncoder::GetPinCLK() {
	return CLK;
};

void IRAM_ATTR RotaryEncoder::Process() {
    if(advconfig)
    {
        currentStateCLK = digitalRead(CLK);
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
        {
            if (digitalRead(DT) != currentStateCLK)
            {
                //ENCODER STEP UP
                if(value >= max)
                {
                    if (loop) value = min;
                }
                else value++;
            }
            else
            {           
                //ENCODER STEP DOWN     
                if(value <= min)
                {
                    if (loop) value = max;
                }
                else value--;
            }
            updated = true;
        }
        lastStateCLK = currentStateCLK;
    }
    else
    {
        currentStateCLK = digitalRead(CLK);
        if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
        {
            if (digitalRead(DT) != currentStateCLK)
            {
            value++;
            }
            else
            {
            value--;
            }
            updated = true;
        }
        lastStateCLK = currentStateCLK;
    }
};

bool RotaryEncoder::Updated() {
    if(updated)
    {
        updated = false;
        return true;
    }
    else return false;
};

int RotaryEncoder::Value() {
	return value;
};