#pragma once
#include <Arduino.h>

namespace Safety {

    void init(float maxSafeTempC);

    // Call this every loop with latest readings
    void update(float tempC, int rawADC);

    bool isFault();
    const char* getFaultReason();

    // Hard shutdown (e.g., called directly from control logic)
    void shutdown(const char* reason);
}
