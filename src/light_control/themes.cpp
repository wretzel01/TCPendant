#include "themes.h"

// ---------------------------------------------
// Theme definitions
// ---------------------------------------------
const Theme THEMES[THEME_COUNT] = {
    { COLOR_AMBER,     ANIM_BREATHE, 255 },
    { COLOR_ORANGE,    ANIM_FLICKER, 255 },
    { COLOR_ICE_BLUE,  ANIM_PULSE,   255 },
    { {180,0,255},     ANIM_TWINKLE, 255 },
    { COLOR_RED,       ANIM_TWINKLE, 255 },
    { COLOR_ORANGE,    ANIM_FLICKER, 255 },
    { {255,60,120},    ANIM_BREATHE, 255 },
    { COLOR_SOFT_WHITE,ANIM_BREATHE, 200 },
    { COLOR_WHITE,     ANIM_RAINBOW, 255 }
};

// ---------------------------------------------
// Theme lookup helper
// ---------------------------------------------
const Theme& getTheme(ThemeId id) {
    if (id >= THEME_COUNT) {
        return THEMES[THEME_AMBER]; // fallback
    }
    return THEMES[id];
}
