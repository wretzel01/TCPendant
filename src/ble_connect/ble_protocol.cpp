#include "ble_protocol.h"
#include <Arduino.h>

// ---------------------------------------------------------
// Internal state
// ---------------------------------------------------------
static float targetTemp = 40.0f;   // default
static uint8_t mode = 0;           // 0 = off, 1 = heat

static float currentTemp = 0.0f;
static uint8_t currentPWM = 0;

static uint32_t cmdVersion = 0;

// ---------------------------------------------------------
// Apply incoming target temperature
// ---------------------------------------------------------
void BLEProtocol::applyTargetTemp(float t) {
    // Clamp for safety
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
    if (m > 1) return;  // invalid

    mode = m;
    cmdVersion++;

    Serial.print("Protocol: Mode set to ");
    Serial.println(mode);
}

// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------
float BLEProtocol::getTargetTemp() {
    return targetTemp;
}

uint8_t BLEProtocol::getMode() {
    return mode;
}

float BLEProtocol::getCurrentTemp() {
    return currentTemp;
}

uint8_t BLEProtocol::getCurrentPWM() {
    return currentPWM;
}

uint32_t BLEProtocol::getCmdVersion() {
    return cmdVersion;
}

// ---------------------------------------------------------
// Internal updates (called by thermal control)
// ---------------------------------------------------------
void BLEProtocol::updateCurrentTemp(float t) {
    currentTemp = t;
}

void BLEProtocol::updateCurrentPWM(uint8_t p) {
    currentPWM = p;
}
