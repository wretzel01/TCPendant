#include "thermal_control.h"
#include "thermistor.h"
#include "heater.h"
#include "filter.h"

namespace ThermalControl {

    static float lastTemp = NAN;
    static uint8_t lastPWM = 0;

    // ---------------------------------------------------------
    // Initialization
    // ---------------------------------------------------------
    void init(int thermPin, int heaterPin, float filterAlpha) {
        Thermistor::init(thermPin);
        Heater::init(heaterPin);
        Filter::init(filterAlpha);

        Serial.println("[ThermalControl] Initialized");
    }

    // ---------------------------------------------------------
    // Main control loop
    // ---------------------------------------------------------
    void loop(float targetTemp, float hysteresis) {

        float rawTemp = Thermistor::readRawCelsius();
        float tempC = Filter::apply(rawTemp);
        lastTemp = tempC;

        // --- Heating hysteresis (your original logic) ---
        static bool heating = false;

        if (!heating && tempC < (targetTemp - hysteresis)) {
            heating = true;
        }

        if (heating && tempC > targetTemp) {
            heating = false;
        }

        // --- BOOST/CRUISE hysteresis (new logic) ---
        static bool boostMode = false;

        float heatingEnter = targetTemp - hysteresis;
        float boostEnter   = heatingEnter - hysteresis;  // reuse hysteresis
        float boostExit    = heatingEnter;               // reuse hysteresis

        if (heating) {
            if (!boostMode && tempC < boostEnter)
                boostMode = true;

            if (boostMode && tempC > boostExit)
                boostMode = false;
        } else {
            boostMode = false;  // safety: no boost when heating is off
        }

        // --- Output ---
        uint8_t pwm;

        if (!heating)
            pwm = 0;
        else if (boostMode)
            pwm = 255;
        else
            pwm = Heater::cruisePWM;

        Heater::setPWM(pwm);
        lastPWM = pwm;

        // --- Debug print ---
        static unsigned long lastPrint = 0;
        unsigned long now = millis();
        if (now - lastPrint > 500) {
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
