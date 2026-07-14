#include "protocol.h"

namespace Protocol {

    static float targetTemp = 42.0;
    static uint8_t mode = 1;

    void setTargetTemp(float t) {
        targetTemp = clampTemp(t);
    }

    void setMode(uint8_t m) {
        mode = clampMode(m);
    }

    float getTargetTemp() {
        return targetTemp;
    }

    uint8_t getMode() {
        return mode;
    }

    float clampTemp(float t) {
        if (t < 35.0) return 35.0;
        if (t > 45.0) return 45.0;
        return t;
    }

    uint8_t clampMode(uint8_t m) {
        if (m < 1) return 1;
        if (m > 3) return 3;
        return m;
    }
}
