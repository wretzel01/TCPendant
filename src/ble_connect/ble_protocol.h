#pragma once
#include <stdint.h>
#include "light_control/animations.h"
#include "light_control/themes.h"

namespace BLEProtocol {

    // Existing thermal controls
    void applyTargetTemp(float t);
    void applyMode(uint8_t m);

    float getTargetTemp();
    uint8_t getMode();
    float getCurrentTemp();
    uint8_t getCurrentPWM();
    uint32_t getCmdVersion();

    void updateCurrentTemp(float t);
    void updateCurrentPWM(uint8_t p);

    float getBatteryVoltage();
    float getBatteryCurrent();
    int   getBatteryPercent();

    // ---------------------------------------------------------
    // ⭐ NEW: LED controls
    // ---------------------------------------------------------

    // Raw RGB (for direct color control)
    void applyLEDColor(uint8_t r, uint8_t g, uint8_t b);
    uint8_t getLED_R();
    uint8_t getLED_G();
    uint8_t getLED_B();

    // Animation (direct control)
    void applyLEDAnimation(AnimationId id);
    AnimationId getLEDAnimation();

    // Theme (preset control)
    void applyLEDTheme(ThemeId id);
    ThemeId getLEDTheme();

    // Brightness (0–255)
    void applyLEDBrightness(uint8_t b);
    uint8_t getLEDBrightness();
}
