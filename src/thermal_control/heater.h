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

    // Cruise power (maintenance mode)
    extern uint8_t cruisePWM;
    void setCruisePWM(uint8_t duty);
    void onCruise();

    // Turn heater off
    void off();

    // Debug accessor
    uint8_t getLastPWM();
}

#endif
