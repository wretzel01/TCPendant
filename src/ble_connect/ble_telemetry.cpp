#include "ble_telemetry.h"
#include "ble_protocol.h"
#include "ble_init.h"
#include "battery_monitor/battery_monitor.h"

#include <Arduino.h>
#include <NimBLECharacteristic.h>

extern NimBLECharacteristic* charStateSync;

// ---------------------------------------------------------
// Telemetry packet (sent to the app)
// ---------------------------------------------------------
struct TelemetryPacket {
    float temp;
    uint8_t pwm;
    uint8_t mode;
    uint16_t flags;

    float batteryVoltage;
    uint8_t batteryPercent;
    float batteryCurrent;

    uint8_t ledR;
    uint8_t ledG;
    uint8_t ledB;

    uint8_t ledAnimation;
    uint8_t ledTheme;
    uint8_t ledBrightness;
};

// ---------------------------------------------------------
// Send telemetry packet
// ---------------------------------------------------------
void BLETelemetry::sendPacket() {
    if (!charStateSync) return;

    TelemetryPacket pkt;

    pkt.temp           = BLEProtocol::getCurrentTemp();
    pkt.pwm            = BLEProtocol::getCurrentPWM();
    pkt.mode           = BLEProtocol::getMode();
    pkt.flags          = 0;

    pkt.batteryVoltage = getBatteryVoltage();
    pkt.batteryPercent = getBatteryPercent();
    pkt.batteryCurrent = getBatteryCurrent();

    pkt.ledR           = BLEProtocol::getLED_R();
    pkt.ledG           = BLEProtocol::getLED_G();
    pkt.ledB           = BLEProtocol::getLED_B();

    pkt.ledAnimation   = BLEProtocol::getLEDAnimation();
    pkt.ledTheme       = BLEProtocol::getLEDTheme();
    pkt.ledBrightness  = BLEProtocol::getLEDBrightness();

    charStateSync->setValue((uint8_t*)&pkt, sizeof(pkt));
    charStateSync->notify();
}

// ---------------------------------------------------------
// Telemetry loop (5 Hz)
// ---------------------------------------------------------
void BLETelemetry::loop() {
    static uint32_t last = 0;
    uint32_t now = millis();

    if (now - last >= 200) {
        last = now;
        sendPacket();
    }
}
