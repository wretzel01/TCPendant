#include <Arduino.h>
#include "thermal_control/thermal_control.h"
#include "ble_connect/ble_connect.h"
#include "ble_connect/ble_protocol.h"
#include "ble_connect/ble_telemetry.h"
#include "battery_monitor/battery_monitor.h"
#include "light_control/light_control.h"

#include <Wire.h>

// -----------------------------
// User‑configurable parameters
// -----------------------------
float targetTempC   = 42.0;
float hysteresisC   = 2.0;
float filterAlpha   = 0.10;

// Hardware pins
const int THERM_PIN  = 2;
const int HEATER_PIN = 3;
const int LED_PIN    = 4;

// Loop timing
const unsigned long LOOP_INTERVAL_MS = 100;
unsigned long lastLoop = 0;

void setup() {
    Serial.begin(115200);
    delay(300);

    Serial.println("\n=== Thermal Control v2 ===");

    batteryMonitorInit();

    ThermalControl::init(THERM_PIN, HEATER_PIN, filterAlpha);
    BLEConnect::init();
    LightControl::init(LED_PIN);

    Serial.println("[main] Setup complete");
}

void loop() {
    unsigned long now = millis();

    // ---------------------------------------------------------
    // Thermal loop (10 Hz)
    // ---------------------------------------------------------
    if (now - lastLoop >= LOOP_INTERVAL_MS) {
        lastLoop = now;

        targetTempC = BLEProtocol::getTargetTemp();
        uint8_t mode = BLEProtocol::getMode();

        ThermalControl::loop(targetTempC, hysteresisC);

        BLEProtocol::updateCurrentTemp(ThermalControl::getLastTemperature());
        BLEProtocol::updateCurrentPWM(ThermalControl::getLastPWM());

        BLETelemetry::loop();
    }

    // ---------------------------------------------------------
    // BLE event loop
    // ---------------------------------------------------------
    BLEConnect::loop();

    // ---------------------------------------------------------
    // LED control routing (new LightControl API)
    // ---------------------------------------------------------

    // Theme selection (enables theme mode)
    LightControl::setTheme(BLEProtocol::getLEDTheme());

    // Raw RGB (enables raw mode if used)
    LightControl::setColor(
        BLEProtocol::getLED_R(),
        BLEProtocol::getLED_G(),
        BLEProtocol::getLED_B()
    );

    // Raw brightness (enables raw mode if used)
    LightControl::setBrightness(
        BLEProtocol::getLEDBrightness()
    );

    // Raw animation (enables raw mode if used)
    LightControl::setAnimation(
        BLEProtocol::getLEDAnimation()
    );

    // LED update
    LightControl::loop();

    // Give NimBLE a chance even if CDC is misbehaving
    delay(1);
}
