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

        ThermalControl::loop(targetTempC, hysteresisC, mode);

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

    static ThemeId lastTheme = THEME_NONE;
    static uint8_t lastR = 255, lastG = 191, lastB = 0;
    static uint8_t lastBrightness = 255;
    static AnimationId lastAnimation = ANIM_NONE;

    ThemeId newTheme = BLEProtocol::getLEDTheme();
    if (newTheme != lastTheme) {
        lastTheme = newTheme;
        LightControl::setTheme(newTheme);
    }

    uint8_t r = BLEProtocol::getLED_R();
    uint8_t g = BLEProtocol::getLED_G();
    uint8_t b = BLEProtocol::getLED_B();
    if (r != lastR || g != lastG || b != lastB) {
        lastR = r; lastG = g; lastB = b;
        LightControl::setColor(r, g, b);
    }

    uint8_t brightness = BLEProtocol::getLEDBrightness();
    if (brightness != lastBrightness) {
        lastBrightness = brightness;
        LightControl::setBrightness(brightness);
    }

    AnimationId anim = BLEProtocol::getLEDAnimation();
    if (anim != lastAnimation) {
        lastAnimation = anim;
        LightControl::setAnimation(anim);
    }

    LightControl::loop();

    // Give NimBLE a chance even if CDC is misbehaving
    delay(1);
}