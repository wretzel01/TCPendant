#include "ble_protocol.h"
#include "battery_monitor/battery_monitor.h"
#include <Arduino.h>

// ---------------------------------------------------------
// Internal state — thermal
// ---------------------------------------------------------
static float targetTemp = 40.0f;
static uint8_t mode = 1;

static float currentTemp = 0.0f;
static uint8_t currentPWM = 0;

static uint32_t cmdVersion = 0;

// ---------------------------------------------------------
// Internal state — LED
// ---------------------------------------------------------
static uint8_t ledR = 255;
static uint8_t ledG = 80;
static uint8_t ledB = 0;

static AnimationId ledAnimation = ANIM_FLICKER;
static ThemeId ledTheme = THEME_AMBER;

static uint8_t ledBrightness = 255;

// ---------------------------------------------------------
// Apply incoming target temperature
// ---------------------------------------------------------
void BLEProtocol::applyTargetTemp(float t) {
    if (t < 35.0f) t = 35.0f;
    if (t > 45.0f) t = 45.0f;

    targetTemp = t;
    cmdVersion++;

    Serial.print("Protocol: TargetTemp set to ");
    Serial.println(targetTemp);
}

// ---------------------------------------------------------
// Apply incoming mode
// ---------------------------------------------------------
void BLEProtocol::applyMode(uint8_t m) {
    if (m > 2) return;

    mode = m;
    cmdVersion++;

    Serial.print("Protocol: Mode set to ");
    Serial.println(mode);
}

// ---------------------------------------------------------
// ⭐ NEW: Apply LED color
// ---------------------------------------------------------
void BLEProtocol::applyLEDColor(uint8_t r, uint8_t g, uint8_t b) {
    ledR = r;
    ledG = g;
    ledB = b;
    cmdVersion++;

    Serial.println("Protocol: LED Color updated");
}

uint8_t BLEProtocol::getLED_R() { return ledR; }
uint8_t BLEProtocol::getLED_G() { return ledG; }
uint8_t BLEProtocol::getLED_B() { return ledB; }

// ---------------------------------------------------------
// ⭐ NEW: Apply LED animation
// ---------------------------------------------------------
void BLEProtocol::applyLEDAnimation(AnimationId id) {
    ledAnimation = id;
    cmdVersion++;

    Serial.print("Protocol: LED Animation set to ");
    Serial.println((uint8_t)id);
}

AnimationId BLEProtocol::getLEDAnimation() {
    return ledAnimation;
}

// ---------------------------------------------------------
// ⭐ NEW: Apply LED theme
// ---------------------------------------------------------
void BLEProtocol::applyLEDTheme(ThemeId id) {
    ledTheme = id;
    cmdVersion++;

    Serial.print("Protocol: LED Theme set to ");
    Serial.println((uint8_t)id);
}

ThemeId BLEProtocol::getLEDTheme() {
    return ledTheme;
}

// ---------------------------------------------------------
// ⭐ NEW: Apply LED brightness
// ---------------------------------------------------------
void BLEProtocol::applyLEDBrightness(uint8_t b) {
    ledBrightness = b;
    cmdVersion++;

    Serial.print("Protocol: LED Brightness set to ");
    Serial.println(ledBrightness);
}

uint8_t BLEProtocol::getLEDBrightness() {
    return ledBrightness;
}

// ---------------------------------------------------------
// Getters — thermal
// ---------------------------------------------------------
float BLEProtocol::getTargetTemp() { return targetTemp; }
uint8_t BLEProtocol::getMode() { return mode; }
float BLEProtocol::getCurrentTemp() { return currentTemp; }
uint8_t BLEProtocol::getCurrentPWM() { return currentPWM; }
uint32_t BLEProtocol::getCmdVersion() { return cmdVersion; }

// ---------------------------------------------------------
// Battery passthrough
// ---------------------------------------------------------
float BLEProtocol::getBatteryVoltage() { return getBatteryVoltage(); }
float BLEProtocol::getBatteryCurrent() { return getBatteryCurrent(); }
int   BLEProtocol::getBatteryPercent() { return getBatteryPercent(); }

// ---------------------------------------------------------
// Internal updates
// ---------------------------------------------------------
void BLEProtocol::updateCurrentTemp(float t) { currentTemp = t; }
void BLEProtocol::updateCurrentPWM(uint8_t p) { currentPWM = p; }
