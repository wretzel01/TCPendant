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

        // 1. Read raw temperature
        float rawTemp = Thermistor::readRawCelsius();

        // 2. Apply user-configurable filtering
        float tempC = Filter::apply(rawTemp);
        lastTemp = tempC;

        // 3. True hysteresis control (no chattering)
        static bool heating = false;

        // Lower threshold: turn ON
        if (!heating && tempC < (targetTemp - hysteresis)) {
            heating = true;
        }

        // Upper threshold: turn OFF
        if (heating && tempC > targetTemp) {
            heating = false;
        }

        // Heater output
        uint8_t pwm = heating ? 255 : 0;

        Heater::setPWM(pwm);
        lastPWM = pwm;

        // 4. Debug output (throttled)
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
