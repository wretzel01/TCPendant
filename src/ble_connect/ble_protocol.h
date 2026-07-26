#pragma once
#include <stdint.h>

namespace BLEProtocol {

    // Incoming commands
    void applyTargetTemp(float t);
    void applyMode(uint8_t m);

    // Internal state getters
    float getTargetTemp();
    uint8_t getMode();

    float getCurrentTemp();
    uint8_t getCurrentPWM();

    // Command versioning
    uint32_t getCmdVersion();

    // Internal updates (called by thermal control)
    void updateCurrentTemp(float t);
    void updateCurrentPWM(uint8_t p);
}
