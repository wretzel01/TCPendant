#include "colors.h"

// ---------------------------------------------
// Named colors
// ---------------------------------------------
const Color COLOR_AMBER      = {255, 80, 0};
const Color COLOR_GOLD       = {220, 160, 0};
const Color COLOR_ORANGE     = {255, 40, 0};
const Color COLOR_RED        = {255, 0, 0};
const Color COLOR_GREEN      = {0, 255, 0};
const Color COLOR_BLUE       = {0, 0, 255};
const Color COLOR_WHITE      = {255, 255, 255};
const Color COLOR_SOFT_WHITE = {200, 200, 200};
const Color COLOR_ICE_BLUE   = {80, 160, 255};

// ---------------------------------------------
// Brightness scaling
// ---------------------------------------------
Color scale(const Color& c, float factor) {
    if (factor < 0.0f) factor = 0.0f;
    if (factor > 1.0f) factor = 1.0f;

    return {
        (uint8_t)(c.r * factor),
        (uint8_t)(c.g * factor),
        (uint8_t)(c.b * factor)
    };
}

// ---------------------------------------------
// Blend two colors
// ---------------------------------------------
Color blend(const Color& a, const Color& b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return {
        (uint8_t)(a.r + (b.r - a.r) * t),
        (uint8_t)(a.g + (b.g - a.g) * t),
        (uint8_t)(a.b + (b.b - a.b) * t)
    };
}

// ---------------------------------------------
// Warm/cool tinting (thermal effect)
// warmth: -1.0 = cool, 0 = neutral, +1.0 = warm
// ---------------------------------------------
Color tint(const Color& base, float warmth) {
    if (warmth < -1.0f) warmth = -1.0f;
    if (warmth > 1.0f)  warmth = 1.0f;

    // Warm = more red, less blue
    // Cool = more blue, less red
    float warmFactor = (warmth > 0) ? warmth : 0;
    float coolFactor = (warmth < 0) ? -warmth : 0;

    return {
        (uint8_t)(base.r + 80 * warmFactor - 40 * coolFactor),
        base.g,
        (uint8_t)(base.b - 40 * warmFactor + 80 * coolFactor)
    };
}
