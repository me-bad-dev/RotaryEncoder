#include "RotaryEncoder.h"
#include <Arduino.h>

RotaryEncoder::RotaryEncoder(uint8_t _dt, uint8_t _clk, int _min, int _max, int _actual, bool _loop) {   
    DT = _dt;
    CLK = _clk;

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
    int currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK && currentStateCLK == HIGH) {
        if (digitalRead(DT) != currentStateCLK) {
            value = (value >= max && loop) ? min : value + 1;
        } else {
            value = (value <= min && loop) ? max : value - 1;
        }
        updated = true;
    }
    lastStateCLK = currentStateCLK;
};

bool RotaryEncoder::Updated() {
    if (updated) {
        updated = false;
        return true;
    }
    return false;
};

int RotaryEncoder::Value() {
	return value;
};
