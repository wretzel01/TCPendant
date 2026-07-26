#include <Arduino.h>
#include "thermal_control/thermal_control.h"
#include "ble_connect/ble_connect.h"
#include "ble_connect/ble_protocol.h"
#include "ble_connect/ble_telemetry.h"

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
    BLEConnect::init();

    Serial.println("[main] Setup complete");
}

void loop() {
    unsigned long now = millis();

    if (now - lastLoop >= LOOP_INTERVAL_MS) {
        lastLoop = now;

        targetTempC = BLEProtocol::getTargetTemp();
        uint8_t mode = BLEProtocol::getMode();

        ThermalControl::loop(targetTempC, hysteresisC);

        BLEProtocol::updateCurrentTemp(ThermalControl::getLastTemperature());
        BLEProtocol::updateCurrentPWM(ThermalControl::getLastPWM());

        BLETelemetry::loop();
    }

    BLEConnect::loop();

    // Give NimBLE a chance even if CDC is misbehaving
    delay(1);
}



