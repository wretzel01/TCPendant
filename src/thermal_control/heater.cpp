#include "heater.h"
#include <math.h>

namespace Heater {

    static int heaterPin = 3;
    static uint8_t lastPWM = 0;

    // Default cruise power
    uint8_t cruisePWM = 170;

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
    // Turn heater off
    // ---------------------------------------------------------
    void off() {
        setPWM(0);
    }

    // ---------------------------------------------------------
    // Mode + Temperature Scaled Heating
    // ---------------------------------------------------------
    void apply(float delta, uint8_t mode) {

        // OFF mode
        if (mode == 0) {
            off();
            return;
        }

        uint8_t pwm = 0;

        // ---------------------------------------------------------
        // NORMAL MODE — exponential smoothing
        // ---------------------------------------------------------
        if (mode == 1) {

            if (delta <= 0.0f) {
                pwm = 0;   // at or above target
            } else {
                const float k = 0.6f;  // exponential steepness
                float normalized = 1.0f - expf(-k * delta);

                pwm = (uint8_t)(normalized * cruisePWM);

                if (pwm > cruisePWM)
                    pwm = cruisePWM;
            }
        }

        // ---------------------------------------------------------
        // HIGH MODE — binary 255 or 0
        // ---------------------------------------------------------
        else if (mode == 2) {

            if (delta > 0.0f) {
                pwm = 255;   // full blast
            } else {
                pwm = 0;     // off
            }
        }

        setPWM(pwm);
    }

    // ---------------------------------------------------------
    // Debug accessor
    // ---------------------------------------------------------
    uint8_t getLastPWM() {
        return lastPWM;
    }

} // namespace Heater
