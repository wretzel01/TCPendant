#include "thermal_control.h"
#include "thermistor.h"
#include "heater.h"
#include "filter.h"
#include "ble_connect/ble_protocol.h"

namespace ThermalControl {

    static float lastTemp = NAN;
    static uint8_t lastPWM = 0;

    void init(int thermPin, int heaterPin, float filterAlpha) {
        Thermistor::init(thermPin);
        Heater::init(heaterPin);
        Filter::init(filterAlpha);

        Serial.println("[ThermalControl] Initialized");
    }

    void loop(float targetTemp, float hysteresis, uint8_t mode) {

        float rawTemp = Thermistor::readRawCelsius();
        float tempC = Filter::apply(rawTemp);
        lastTemp = tempC;

        // ---------------------------------------------------------
        // HYSTERESIS STATE
        // ---------------------------------------------------------
        static bool heating = false;

        static float lastTarget = NAN;
        static uint8_t lastMode = 255;

        // ⭐ FIX: Reset hysteresis BEFORE computing delta
        if (targetTemp != lastTarget || mode != lastMode) {
            heating = true;   // <-- THIS is the critical fix
            lastTarget = targetTemp;
            lastMode = mode;
        }

        // Normal hysteresis logic
        if (!heating && tempC < (targetTemp - hysteresis))
            heating = true;

        if (heating && tempC > targetTemp)
            heating = false;

        // ---------------------------------------------------------
        // Compute delta AFTER hysteresis logic
        // ---------------------------------------------------------
        float delta = targetTemp - tempC;

        // If hysteresis says "not heating", force delta negative
        if (!heating)
            delta = -999.0f;

        // ---------------------------------------------------------
        // Heater logic
        // ---------------------------------------------------------
        Heater::apply(delta, mode);
        lastPWM = Heater::getLastPWM();

        // Debug
        static unsigned long lastPrint = 0;
        unsigned long now = millis();
        if (now - lastPrint > 500) {
            Serial.print("Temp: ");
            Serial.print(tempC);
            Serial.print(" C | PWM: ");
            Serial.print(lastPWM);
            Serial.print(" | Mode: ");
            Serial.print(mode);
            Serial.print(" | Heating: ");
            Serial.println(heating ? "YES" : "NO");
            lastPrint = now;
        }
    }

    float getLastTemperature() {
        return lastTemp;
    }

    uint8_t getLastPWM() {
        return lastPWM;
    }

}
