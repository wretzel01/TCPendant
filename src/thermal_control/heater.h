#pragma once
#include <Arduino.h>

namespace Heater {

    void init(int pin, int pwmChannel = 0, int pwmFreq = 5000, int pwmResolution = 8);

    void setPWM(uint8_t duty);   // 0–255
    void onFull();               // 255
    void off();                  // 0

    uint8_t getCurrentPWM();     // for debugging
}
