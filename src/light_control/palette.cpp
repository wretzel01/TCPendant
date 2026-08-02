#include "palette.h"

// ---------------------------------------------
// Warm palette (fire, sunset, ember)
// ---------------------------------------------
static const Color warmColors[] = {
    COLOR_AMBER,
    COLOR_ORANGE,
    COLOR_RED,
    {255, 120, 40},   // molten gold
    {200, 60, 0}      // deep ember
};

const Palette PALETTE_WARM = {
    warmColors,
    sizeof(warmColors) / sizeof(Color)
};

// ---------------------------------------------
// Cool palette (ice, ocean, aurora)
// ---------------------------------------------
static const Color coolColors[] = {
    COLOR_ICE_BLUE,
    {60, 120, 255},   // ocean blue
    {0, 200, 255},    // cyan
    {0, 160, 200},    // teal
    {80, 200, 255}    // frost glow
};

const Palette PALETTE_COOL = {
    coolColors,
    sizeof(coolColors) / sizeof(Color)
};

// ---------------------------------------------
// Magic palette (purples, teals, fantasy)
// ---------------------------------------------
static const Color magicColors[] = {
    {180, 0, 255},    // violet
    {120, 0, 200},    // deep purple
    {0, 180, 255},    // bright teal
    {255, 0, 180},    // magenta
    {80, 0, 120}      // shadow purple
};

const Palette PALETTE_MAGIC = {
    magicColors,
    sizeof(magicColors) / sizeof(Color)
};

// ---------------------------------------------
// Christmas palette (red, green, gold)
// ---------------------------------------------
static const Color christmasColors[] = {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_GOLD,
    {255, 255, 255}   // white sparkle
};

const Palette PALETTE_CHRISTMAS = {
    christmasColors,
    sizeof(christmasColors) / sizeof(Color)
};

// ---------------------------------------------
// Halloween palette (orange, purple, black)
// ---------------------------------------------
static const Color halloweenColors[] = {
    COLOR_ORANGE,
    {120, 0, 200},    // spooky purple
    {40, 0, 0},       // dim red
    {0, 0, 0}         // black (off pixel)
};

const Palette PALETTE_HALLOWEEN = {
    halloweenColors,
    sizeof(halloweenColors) / sizeof(Color)
};

// ---------------------------------------------
// Valentine palette (pink, red, soft white)
// ---------------------------------------------
static const Color valentineColors[] = {
    {255, 60, 120},   // pink
    COLOR_RED,
    COLOR_SOFT_WHITE
};

const Palette PALETTE_VALENTINE = {
    valentineColors,
    sizeof(valentineColors) / sizeof(Color)
};

// ---------------------------------------------
// Soft palette (warm whites)
// ---------------------------------------------
static const Color softColors[] = {
    COLOR_SOFT_WHITE,
    {180, 180, 180},
    {220, 200, 180}
};

const Palette PALETTE_SOFT = {
    softColors,
    sizeof(softColors) / sizeof(Color)
};

// ---------------------------------------------
// Pure white palette
// ---------------------------------------------
static const Color whiteColors[] = {
    COLOR_WHITE,
    {240, 240, 240},
    {200, 200, 200}
};

const Palette PALETTE_WHITE = {
    whiteColors,
    sizeof(whiteColors) / sizeof(Color)
};
