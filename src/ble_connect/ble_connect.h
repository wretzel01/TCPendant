#pragma once
#include <stdint.h>

namespace BLEConnect {

    void init();
    void loop();

    // Values coming FROM the phone
    float getTargetTemp();
    uint8_t getMode();

    // Values going TO the phone
    void setCurrentTemp(float t);
    void setCurrentPWM(uint8_t p);
}
