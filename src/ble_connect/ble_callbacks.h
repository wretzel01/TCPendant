#pragma once
#include <NimBLECharacteristic.h>

namespace BLECallbacks {
    void registerCallbacks(NimBLECharacteristic* charTargetTemp,
                           NimBLECharacteristic* charMode);
}
