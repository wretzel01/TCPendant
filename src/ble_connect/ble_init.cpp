#include "ble_init.h"
#include "ble_callbacks.h"
#include "ble_telemetry.h"
#include "ble_protocol.h"

#include <NimBLEDevice.h>
#include <WiFi.h>
#include "esp_gap_ble_api.h"

// ---------------------------------------------------------
// Internal characteristic pointers
// ---------------------------------------------------------
NimBLECharacteristic* charTargetTemp = nullptr;
NimBLECharacteristic* charMode       = nullptr;
NimBLECharacteristic* charCurTemp    = nullptr;
NimBLECharacteristic* charCurPWM     = nullptr;
NimBLECharacteristic* charStateSync  = nullptr;

// ---------------------------------------------------------
// Server Callbacks (NO override — your NimBLE version requires this)
// ---------------------------------------------------------
class ServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* s, ble_gap_conn_desc* desc) {
        Serial.println("BLE: Connected");
    }

    void onDisconnect(NimBLEServer* s, ble_gap_conn_desc* desc) {
        Serial.println("BLE: Disconnected");

        BLEProtocol::applyMode(0);
        s->startAdvertising();
    }
};

// ---------------------------------------------------------
// BLE Initialization
// ---------------------------------------------------------
void BLEInit::setup() {
    WiFi.mode(WIFI_OFF);

    esp_ble_gap_config_local_privacy(false);

    NimBLEDevice::init("TCPendant");
    delay(250);

    NimBLEServer* server = NimBLEDevice::createServer();
    server->setCallbacks(new ServerCallbacks());

    NimBLEService* svc = server->createService("1234");

    charTargetTemp = svc->createCharacteristic("1235",
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    charMode = svc->createCharacteristic("1236",
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    charCurTemp = svc->createCharacteristic("1237",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charCurPWM = svc->createCharacteristic("1238",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charStateSync = svc->createCharacteristic("1239",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charCurTemp->createDescriptor("2902");
    charCurPWM->createDescriptor("2902");
    charStateSync->createDescriptor("2902");

    svc->start();

    BLECallbacks::registerCallbacks(charTargetTemp, charMode);

    NimBLEAdvertisementData advData;
    advData.setName("TCPendant");
    advData.setCompleteServices(NimBLEUUID("1234"));

    NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
    adv->setAdvertisementData(advData);
    adv->start();

    Serial.println("BLE: Advertising started");
}
