#pragma once
#include <NimBLECharacteristic.h>

namespace BLECallbacks {

    void registerCallbacks(
        NimBLECharacteristic* charTargetTemp,
        NimBLECharacteristic* charMode,
        NimBLECharacteristic* charLEDColor,
        NimBLECharacteristic* charLEDAnimation,
        NimBLECharacteristic* charLEDTheme,
        NimBLECharacteristic* charLEDBrightness
    );

}
