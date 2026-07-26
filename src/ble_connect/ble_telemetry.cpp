#include "ble_telemetry.h"
#include "ble_protocol.h"

#include <Arduino.h>
#include <NimBLECharacteristic.h>

extern NimBLECharacteristic* charStateSync;

struct TelemetryPacket {
    float temp;
    uint8_t pwm;
    uint8_t mode;
    uint16_t flags;
};

void BLETelemetry::sendPacket() {
    Serial.println("[FW] sendPacket() called");

    if (!charStateSync) {
        Serial.println("[FW] charStateSync is NULL");
        return;
    }

    TelemetryPacket pkt;
    pkt.temp  = BLEProtocol::getCurrentTemp();
    pkt.pwm   = BLEProtocol::getCurrentPWM();
    pkt.mode  = BLEProtocol::getMode();
    pkt.flags = 0;

    Serial.print("[FW] Packet bytes: ");
    Serial.println(sizeof(pkt));

    charStateSync->setValue((uint8_t*)&pkt, sizeof(pkt));

    Serial.println("[FW] Calling notify()");
    charStateSync->notify();
    Serial.println("[FW] notify() returned");
}

void BLETelemetry::loop() {
    static uint32_t last = 0;
    uint32_t now = millis();

    if (now - last < 200) return;  // 5 Hz
    last = now;

    sendPacket();
}
