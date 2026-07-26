#include "ble_callbacks.h"
#include "ble_protocol.h"

#include <Arduino.h>
#include <NimBLEDevice.h>

// ---------------------------------------------------------
// TargetTemp Write Callback
// ---------------------------------------------------------
class TargetTempCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        const std::string raw = c->getValue();
        Serial.print("BLE: Raw TargetTemp = ");
        Serial.println(raw.c_str());

        float t = atof(raw.c_str());

        // Validation
        if (t < 35.0f || t > 45.0f) {
            Serial.println("BLE: TargetTemp out of range, ignoring");
            return;
        }

        Serial.print("BLE: Parsed TargetTemp = ");
        Serial.println(t);

        BLEProtocol::applyTargetTemp(t);
    }
};

// ---------------------------------------------------------
// Mode Write Callback
// ---------------------------------------------------------
class ModeCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        const std::string raw = c->getValue();
        Serial.print("BLE: Raw Mode = ");
        Serial.println(raw.c_str());

        if (raw.empty()) {
            Serial.println("BLE: Empty mode write, ignoring");
            return;
        }

        uint8_t m = raw[0];

        // Validation
        if (m > 1) {
            Serial.println("BLE: Invalid mode, ignoring");
            return;
        }

        Serial.print("BLE: Parsed Mode = ");
        Serial.println(m);

        BLEProtocol::applyMode(m);
    }
};

// ---------------------------------------------------------
// Register Callbacks
// ---------------------------------------------------------
void BLECallbacks::registerCallbacks(NimBLECharacteristic* charTargetTemp,
                                     NimBLECharacteristic* charMode)
{
    charTargetTemp->setCallbacks(new TargetTempCallback());
    charMode->setCallbacks(new ModeCallback());
}
