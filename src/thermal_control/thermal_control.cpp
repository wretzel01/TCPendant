#include "thermal_control.h"
#include "thermistor.h"
#include "heater.h"
#include "safety.h"

namespace ThermalControl {

    static float lastTemp = NAN;
    static uint8_t lastPWM = 0;

    // ---------------------------------------------------------
    // Init
    // ---------------------------------------------------------
    void init(int thermPin, int heaterPin) {
        Thermistor::init(thermPin);
        Heater::init(heaterPin);
        Safety::init(42.0);   // max temp stays here for now
        Serial.println("[ThermalControl] Initialized");
    }

    // ---------------------------------------------------------
    // Main control loop
    // ---------------------------------------------------------
    void loop(float targetTemp, float hysteresis) {
        int rawADC = Thermistor::readADC();
        float tempC = Thermistor::readCelsius();
        lastTemp = tempC;

        // Safety first
        Safety::update(tempC, rawADC);

        if (Safety::isFault()) {
            Heater::off();
            lastPWM = 0;
            return;
        }

        // -----------------------------
        // Hysteresis + PWM control
        // -----------------------------
        if (tempC < targetTemp - hysteresis) {
            Heater::onFull();
            lastPWM = 255;
        }
        else if (tempC > targetTemp + hysteresis) {
            Heater::off();
            lastPWM = 0;
        }
        else {
            uint8_t pwm = 100;
            Heater::setPWM(pwm);
            lastPWM = pwm;
        }

        // -----------------------------
        // Throttled debug printing
        // -----------------------------
        static unsigned long lastPrint = 0;
        unsigned long now = millis();

        if (now - lastPrint > 500) {   // print twice per second
            Serial.print("Temp: ");
            Serial.print(tempC);
            Serial.print(" C | PWM: ");
            Serial.println(lastPWM);
            lastPrint = now;
        }
    }


    // ---------------------------------------------------------
    // Debug accessors
    // ---------------------------------------------------------
    float getLastTemperature() {
        return lastTemp;
    }

    uint8_t getLastPWM() {
        return lastPWM;
    }

}
