#include "battery_monitor.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

namespace BatteryMonitor {

    static Adafruit_INA219 ina219;

    static float voltageFiltered = NAN;
    static float currentFiltered = NAN;

    static constexpr float SMOOTHING = 0.2f;

    void init(int sdaPin, int sclPin) {
        Wire.begin(sdaPin, sclPin);

        if (!ina219.begin()) {
            Serial.println("[BatteryMonitor] INA219 not found");
            voltageFiltered = 0.0f;
            currentFiltered = 0.0f;
        } else {
            Serial.println("[BatteryMonitor] INA219 initialized");
        }
    }

    void loop() {
        float v = ina219.getBusVoltage_V();
        float c = ina219.getCurrent_mA();

        // Apply smoothing
        if (isnan(voltageFiltered)) voltageFiltered = v;
        if (isnan(currentFiltered)) currentFiltered = c;

        voltageFiltered = SMOOTHING * voltageFiltered + (1.0f - SMOOTHING) * v;
        currentFiltered = SMOOTHING * currentFiltered + (1.0f - SMOOTHING) * c;

        // Debug print (same style as ThermalControl)
        static unsigned long lastPrint = 0;
        unsigned long now = millis();
        if (now - lastPrint > 500) {
            Serial.print("[BatteryMonitor] V=");
            Serial.print(voltageFiltered);
            Serial.print("V | I=");
            Serial.print(currentFiltered);
            Serial.println("mA");
            lastPrint = now;
        }
    }

    float getVoltage() {
        return voltageFiltered;
    }

    float getCurrent() {
        return currentFiltered;
    }

    int getPercent() {
        float v = voltageFiltered;

        if (v >= 4.20f) return 100;
        if (v >= 4.10f) return 90;
        if (v >= 4.00f) return 80;
        if (v >= 3.90f) return 70;
        if (v >= 3.85f) return 60;
        if (v >= 3.80f) return 50;
        if (v >= 3.75f) return 40;
        if (v >= 3.70f) return 30;
        if (v >= 3.65f) return 20;
        if (v >= 3.55f) return 10;
        if (v >= 3.45f) return 5;
        return 0;
    }

}
