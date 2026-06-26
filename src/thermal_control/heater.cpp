#include "heater.h"

namespace Heater {

    static int heaterPin = 3;
    static int channel = 0;
    static uint8_t currentPWM = 0;

    // ---------------------------------------------------------
    // Initialization
    // ---------------------------------------------------------
    void init(int pin, int pwmChannel, int pwmFreq, int pwmResolution) {
        heaterPin = pin;
        channel = pwmChannel;

        // Configure PWM
        ledcSetup(channel, pwmFreq, pwmResolution);
        ledcAttachPin(heaterPin, channel);

        // Start OFF
        setPWM(0);
    }

    // ---------------------------------------------------------
    // Set PWM duty (0–255)
    // ---------------------------------------------------------
    void setPWM(uint8_t duty) {
        currentPWM = duty;
        ledcWrite(channel, duty);
    }

    // ---------------------------------------------------------
    // Full power (255)
    // ---------------------------------------------------------
    void onFull() {
        setPWM(255);
    }

    // ---------------------------------------------------------
    // Heater OFF
    // ---------------------------------------------------------
    void off() {
        setPWM(0);
    }

    // ---------------------------------------------------------
    // For debugging
    // ---------------------------------------------------------
    uint8_t getCurrentPWM() {
        return currentPWM;
    }

}
