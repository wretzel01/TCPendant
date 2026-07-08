#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>

namespace Heater {

    // Initialize heater MOSFET pin
    void init(int pin);

    // Set heater PWM (0–255)
    void setPWM(uint8_t duty);

    // Full power (255)
    void onFull();

    // Turn heater off
    void off();

    // Debug accessor
    uint8_t getLastPWM();
}

#endif
