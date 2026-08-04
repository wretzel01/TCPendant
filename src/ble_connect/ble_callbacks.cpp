#include "ble_callbacks.h"
#include "ble_protocol.h"
#include "light_control/light_control.h"

#include <Arduino.h>
#include <NimBLEDevice.h>

// ---------------------------------------------------------
// Existing characteristic callbacks (unchanged)
// ---------------------------------------------------------

class TargetTempCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        const std::string raw = c->getValue();
        Serial.print("BLE: Raw TargetTemp = ");
        Serial.println(raw.c_str());

        float t = atof(raw.c_str());
        if (t < 35.0f || t > 45.0f) {
            Serial.println("BLE: TargetTemp out of range, ignoring");
            return;
        }

        BLEProtocol::applyTargetTemp(t);
    }
};

class ModeCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        const std::string raw = c->getValue();
        Serial.print("BLE: Raw Mode = ");
        Serial.println(raw.c_str());

        if (raw.empty()) return;

        uint8_t m = raw[0];
        if (m > 2) {
            Serial.println("BLE: Invalid mode, ignoring");
            return;
        }

        BLEProtocol::applyMode(m);
    }
};

class LEDColorCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        std::string raw = c->getValue();
        Serial.print("BLE: Raw LEDColor bytes = ");
        Serial.println(raw.length());

        if (raw.length() != 3) {
            Serial.println("BLE: LEDColor invalid length");
            return;
        }

        BLEProtocol::applyLEDColor(raw[0], raw[1], raw[2]);
    }
};

class LEDAnimationCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        std::string raw = c->getValue();
        if (raw.empty()) return;

        uint8_t id = raw[0];
        Serial.printf("BLE: Parsed LEDAnimation = %u\n", id);

        if (id > ANIM_RAINBOW) {
            Serial.println("BLE: LEDAnimation out of range");
            return;
        }

        BLEProtocol::applyLEDAnimation((AnimationId)id);
    }
};

class LEDThemeCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        std::string raw = c->getValue();
        if (raw.empty()) return;

        uint8_t id = raw[0];
        Serial.printf("BLE: Parsed LEDTheme = %u\n", id);

        if (id >= THEME_COUNT) {
            Serial.println("BLE: LEDTheme out of range");
            return;
        }

        BLEProtocol::applyLEDTheme((ThemeId)id);
        LightControl::setTheme((ThemeId)id);
    }
};


class LEDBrightnessCallback : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* c, NimBLEConnInfo& connInfo) override {
        std::string raw = c->getValue();
        if (raw.empty()) return;

        uint8_t b = raw[0];
        Serial.printf("BLE: Parsed LEDBrightness = %u\n", b);

        BLEProtocol::applyLEDBrightness(b);
    }
};

// ---------------------------------------------------------
// Register characteristic callbacks
// ---------------------------------------------------------
void BLECallbacks::registerCallbacks(
    NimBLECharacteristic* charTargetTemp,
    NimBLECharacteristic* charMode,
    NimBLECharacteristic* charLEDColor,
    NimBLECharacteristic* charLEDAnimation,
    NimBLECharacteristic* charLEDTheme,
    NimBLECharacteristic* charLEDBrightness
) {
    charTargetTemp->setCallbacks(new TargetTempCallback());
    charMode->setCallbacks(new ModeCallback());
    charLEDColor->setCallbacks(new LEDColorCallback());
    charLEDAnimation->setCallbacks(new LEDAnimationCallback());
    charLEDTheme->setCallbacks(new LEDThemeCallback());
    charLEDBrightness->setCallbacks(new LEDBrightnessCallback());
}