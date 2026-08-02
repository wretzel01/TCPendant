#pragma once
#include <stdint.h>
#include "colors.h"
#include "animations.h"
#include "palette.h"

// ---------------------------------------------
// Theme IDs
// ---------------------------------------------
enum ThemeId : uint8_t {
    THEME_NONE = 255,
    THEME_AMBER = 0,
    THEME_FIRE,
    THEME_ICE,
    THEME_MAGIC,
    THEME_CHRISTMAS,
    THEME_HALLOWEEN,
    THEME_VALENTINE,
    THEME_SOFT_WHITE,
    THEME_RAINBOW,
    THEME_COUNT
};

// ---------------------------------------------
// Theme struct
// ---------------------------------------------
struct Theme {
    Color base;             // base color
    AnimationId animation;  // animation behavior
    const Palette* palette; // optional palette
    uint8_t brightness;     // 0–255
};

// ---------------------------------------------
// Extern theme declarations
// ---------------------------------------------
extern const Theme THEMES[THEME_COUNT];

// ---------------------------------------------
// Lookup helper
// ---------------------------------------------
const Theme& getTheme(ThemeId id);
