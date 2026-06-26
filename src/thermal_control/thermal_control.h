#pragma once
#include <Arduino.h>

namespace ThermalControl {

    void init(int thermPin, int heaterPin);

    // main.cpp passes user settings each loop
    void loop(float targetTempC, float hysteresisC);

    float getLastTemperature();
    uint8_t getLastPWM();
}
