#include "ble_init.h"
#include "ble_callbacks.h"
#include "ble_telemetry.h"
#include "ble_protocol.h"

#include <NimBLEDevice.h>
#include <WiFi.h>
#include "esp_gap_ble_api.h"

// ---------------------------------------------------------
// Characteristics
// ---------------------------------------------------------
NimBLECharacteristic* charTargetTemp = nullptr;
NimBLECharacteristic* charMode       = nullptr;
NimBLECharacteristic* charCurTemp    = nullptr;
NimBLECharacteristic* charCurPWM     = nullptr;
NimBLECharacteristic* charStateSync  = nullptr;

// ---------------------------------------------------------
// Server Callbacks (no watchdog)
// ---------------------------------------------------------
class ServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* s, ble_gap_conn_desc* desc) {
        Serial.println("BLE: Connected");
    }

    void onDisconnect(NimBLEServer* s, ble_gap_conn_desc* desc) {
        Serial.println("BLE: Disconnected");
        BLEProtocol::applyMode(0);
        s->startAdvertising();   // always advertise when not connected
    }
};

// ---------------------------------------------------------
// ⭐ Kick Callback — forces advertising restart
// ---------------------------------------------------------
class KickCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& info) override {
        Serial.println("[BLE] Kick received → restarting advertising");
        NimBLEDevice::startAdvertising();
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

    NimBLEService* svc = server->createService("00001234-0000-1000-8000-00805f9b34fb");

    // ---------------------------------------------------------
    // Thermal + Mode
    // ---------------------------------------------------------
    charTargetTemp = svc->createCharacteristic("1235",
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    charMode = svc->createCharacteristic("1236",
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    // ---------------------------------------------------------
    // LED Controls
    // ---------------------------------------------------------
    NimBLECharacteristic* charLEDColor =
        svc->createCharacteristic("1240",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    NimBLECharacteristic* charLEDAnimation =
        svc->createCharacteristic("1241",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    NimBLECharacteristic* charLEDTheme =
        svc->createCharacteristic("1242",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    NimBLECharacteristic* charLEDBrightness =
        svc->createCharacteristic("1243",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    // ---------------------------------------------------------
    // Telemetry
    // ---------------------------------------------------------
    charCurTemp = svc->createCharacteristic("1237",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charCurPWM = svc->createCharacteristic("1238",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charStateSync = svc->createCharacteristic("1239",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    charCurTemp->createDescriptor("2902");
    charCurPWM->createDescriptor("2902");
    charStateSync->createDescriptor("2902");

    // ---------------------------------------------------------
    // ⭐ Kick Characteristic
    // ---------------------------------------------------------
    NimBLECharacteristic* charKick =
        svc->createCharacteristic("1244",
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);

    // ---------------------------------------------------------
    // Start service
    // ---------------------------------------------------------
    svc->start();

    // ---------------------------------------------------------
    // Register callbacks
    // ---------------------------------------------------------
    BLECallbacks::registerCallbacks(
        charTargetTemp,
        charMode,
        charLEDColor,
        charLEDAnimation,
        charLEDTheme,
        charLEDBrightness
    );

    charKick->setCallbacks(new KickCallback());

    // ---------------------------------------------------------
    // Advertising
    // ---------------------------------------------------------
    NimBLEAdvertisementData advData;
    advData.setName("TCPendant");
    advData.setCompleteServices(NimBLEUUID("00001234-0000-1000-8000-00805f9b34fb"));

    NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
    adv->setAdvertisementData(advData);
    adv->start();

    Serial.println("BLE: Advertising started");
}
