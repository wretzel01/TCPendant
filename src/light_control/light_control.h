#pragma once
#include <stdint.h>
#include "animations.h"
#include "themes.h"
#include "colors.h"

namespace LightControl {
    void init(int pin);

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setBrightness(uint8_t b);
    void setAnimation(AnimationId id);
    void setTheme(ThemeId id);

    void loop();
}
