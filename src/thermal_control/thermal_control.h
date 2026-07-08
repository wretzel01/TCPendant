#ifndef THERMAL_CONTROL_H
#define THERMAL_CONTROL_H

#include <Arduino.h>

namespace ThermalControl {

    // Initialize all components
    void init(int thermPin, int heaterPin, float filterAlpha);

    // Main control loop
    void loop(float targetTemp, float hysteresis);

    // Accessors for debugging
    float getLastTemperature();
    uint8_t getLastPWM();
}

#endif
