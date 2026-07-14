#pragma once
#include <stdint.h>

namespace Protocol {

    // Incoming commands from phone
    void setTargetTemp(float t);
    void setMode(uint8_t m);

    // Outgoing telemetry to phone
    float getTargetTemp();
    uint8_t getMode();

    // Optional: validation helpers
    float clampTemp(float t);
    uint8_t clampMode(uint8_t m);
}
