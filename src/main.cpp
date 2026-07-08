#include <Arduino.h>
#include "thermal_control/thermal_control.h"

// -----------------------------
// User‑configurable parameters
// -----------------------------
float targetTempC   = 42.0;   // desired temperature
float hysteresisC   = 2.0;    // deadband around target
float filterAlpha   = 0.10;   // smoothing factor (0.0–1.0)

// Hardware pins
const int THERM_PIN  = 2;     // ADC input
const int HEATER_PIN = 3;     // MOSFET gate

// Loop timing
const unsigned long LOOP_INTERVAL_MS = 100;  // 10 Hz thermal loop
unsigned long lastLoop = 0;

void setup() {
    Serial.begin(115200);
    delay(300);

    Serial.println("\n=== Thermal Control v2 ===");

    ThermalControl::init(THERM_PIN, HEATER_PIN, filterAlpha);

    Serial.println("[main] Setup complete");
}

void loop() {
    unsigned long now = millis();

    if (now - lastLoop >= LOOP_INTERVAL_MS) {
        lastLoop = now;

        ThermalControl::loop(targetTempC, hysteresisC);
    }

    // You can add UI, button handling, BLE, etc. here later.
}
