#include "themes.h"

// ---------------------------------------------
// Theme definitions
// ---------------------------------------------
const Theme THEMES[THEME_COUNT] = {

    // THEME_AMBER
    {
        COLOR_AMBER,
        ANIM_BREATHE,
        &PALETTE_WARM,
        255
    },

    // THEME_FIRE
    {
        COLOR_ORANGE,
        ANIM_FLICKER,
        &PALETTE_WARM,
        255
    },

    // THEME_ICE
    {
        COLOR_ICE_BLUE,
        ANIM_PULSE,
        &PALETTE_COOL,
        255
    },

    // THEME_MAGIC
    {
        {180, 0, 255},   // violet
        ANIM_TWINKLE,
        &PALETTE_MAGIC,
        255
    },

    // THEME_CHRISTMAS
    {
        COLOR_RED,
        ANIM_TWINKLE,
        &PALETTE_CHRISTMAS,
        255
    },

    // THEME_HALLOWEEN
    {
        COLOR_ORANGE,
        ANIM_FLICKER,
        &PALETTE_HALLOWEEN,
        255
    },

    // THEME_VALENTINE
    {
        {255, 60, 120},  // pink
        ANIM_BREATHE,
        &PALETTE_VALENTINE,
        255
    },

    // THEME_SOFT_WHITE
    {
        COLOR_SOFT_WHITE,
        ANIM_BREATHE,
        &PALETTE_SOFT,
        200
    },

    // THEME_RAINBOW
    {
        COLOR_WHITE,     // unused for rainbow
        ANIM_RAINBOW,
        nullptr,
        255
    }
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
