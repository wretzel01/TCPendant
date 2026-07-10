#include "heater.h"

namespace Heater {

    static int heaterPin = 3;      // default MOSFET gate pin
    static uint8_t lastPWM = 0;    // track last duty cycle

    // ---------------------------------------------------------
    // Initialization
    // ---------------------------------------------------------
    void init(int pin) {
        heaterPin = pin;
        pinMode(heaterPin, OUTPUT);
        off();  // ensure heater starts off
    }

    // ---------------------------------------------------------
    // Set PWM duty (0–255)
    // ---------------------------------------------------------
    void setPWM(uint8_t duty) {
        lastPWM = duty;
        analogWrite(heaterPin, duty);
    }

    // ---------------------------------------------------------
    // Full power
    // ---------------------------------------------------------
    void onFull() {
        setPWM(255);
    }

    // ---------------------------------------------------------
    // Cruise power (maintenance mode)
    // ---------------------------------------------------------
    uint8_t cruisePWM = 170;

    void setCruisePWM(uint8_t duty) {
        cruisePWM = duty;
    }

    void onCruise() {
        setPWM(cruisePWM);
    }

    // ---------------------------------------------------------
    // Turn heater off
    // ---------------------------------------------------------
    void off() {
        setPWM(0);
    }

    // ---------------------------------------------------------
    // Debug accessor
    // ---------------------------------------------------------
    uint8_t getLastPWM() {
        return lastPWM;
    }

}
