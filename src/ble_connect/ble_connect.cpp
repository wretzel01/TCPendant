#include <NimBLEDevice.h>
#include <WiFi.h>
#include "esp_gap_ble_api.h"
#include "ble_connect.h"
#include "protocol.h"

#include "mbedtls/base64.h"

static String decodeBase64(const std::string& input) {
    size_t out_len = 0;
    unsigned char out[32];

    int res = mbedtls_base64_decode(
        out, sizeof(out), &out_len,
        (const unsigned char*)input.c_str(),
        input.length()
    );

    if (res != 0) {
        return "";
    }

    return String((char*)out);
}

namespace BLEConnect {

    // BLE characteristic pointers
    static NimBLECharacteristic* charTargetTemp;
    static NimBLECharacteristic* charMode;
    static NimBLECharacteristic* charCurTemp;
    static NimBLECharacteristic* charCurPWM;

    // ---------------------------------------------------------
    // Write Callbacks
    // ---------------------------------------------------------
    class TargetTempCallback : public NimBLECharacteristicCallbacks {
        void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
            Serial.print("Raw TargetTemp value: ");
            Serial.println(c->getValue().c_str());

            float t = atof(c->getValue().c_str());
            Serial.print("Parsed TargetTemp: ");
            Serial.println(t);

            Protocol::setTargetTemp(t);
        }
    };

    class ModeCallback : public NimBLECharacteristicCallbacks {
        void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
            Serial.print("Raw Mode value: ");
            Serial.println(c->getValue().c_str());

            uint8_t m = c->getValue()[0];
            Serial.print("Parsed Mode: ");
            Serial.println(m);

            Protocol::setMode(m);
        }
    };


    // ---------------------------------------------------------
    // BLE Initialization
    // ---------------------------------------------------------
    void init() {
        WiFi.mode(WIFI_OFF);

        NimBLEDevice::init("TCPendant");
        NimBLEDevice::setDeviceName("TCPendant");

        NimBLEServer* server = NimBLEDevice::createServer();
        NimBLEService* svc = server->createService("1234");

        charTargetTemp = svc->createCharacteristic(
            "1235",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
        );

        charTargetTemp->setCallbacks(new TargetTempCallback());

        charMode = svc->createCharacteristic(
            "1236",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
        );
        charMode->setCallbacks(new ModeCallback());

        charCurTemp = svc->createCharacteristic(
            "1237",
            NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
        );
        charCurPWM  = svc->createCharacteristic(
            "1238",
            NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
        );

        // Add CCCD (Client Characteristic Configuration Descriptor)
        charCurTemp->createDescriptor("2902");
        charCurPWM->createDescriptor("2902");


        server->start();

        NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
        adv->setName("TCPendant");     // <-- This is the correct NimBLE-Arduino API
        adv->start();
    }


    // ---------------------------------------------------------
    // BLE housekeeping
    // ---------------------------------------------------------
    void loop() {
        // NimBLE usually doesn't need periodic work,
        // but we keep this for future expansion.
    }

    // ---------------------------------------------------------
    // Outgoing telemetry
    // ---------------------------------------------------------
    void setCurrentTemp(float t) {
        charCurTemp->setValue(String(t));
        charCurTemp->notify();
    }

    void setCurrentPWM(uint8_t p) {
        charCurPWM->setValue(&p, 1);
        charCurPWM->notify();
    }

    // ---------------------------------------------------------
    // Incoming commands
    // ---------------------------------------------------------
    float getTargetTemp() {
        return Protocol::getTargetTemp();
    }

    uint8_t getMode() {
        return Protocol::getMode();
    }

}
