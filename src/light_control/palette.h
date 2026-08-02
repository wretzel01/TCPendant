#pragma once
#include "colors.h"

// ---------------------------------------------
// Palette struct
// ---------------------------------------------
struct Palette {
    const Color* colors;   // pointer to array of colors
    uint8_t count;         // number of colors in the palette
};

// ---------------------------------------------
// Extern palette declarations
// (defined in palette.cpp)
// ---------------------------------------------

// Warm tones (fire, sunset, ember)
extern const Palette PALETTE_WARM;

// Cool tones (ice, ocean, aurora)
extern const Palette PALETTE_COOL;

// Magical / fantasy tones (purples, teals)
extern const Palette PALETTE_MAGIC;

// Holiday palettes
extern const Palette PALETTE_CHRISTMAS;
extern const Palette PALETTE_HALLOWEEN;
extern const Palette PALETTE_VALENTINE;

// Neutral / white-based palettes
extern const Palette PALETTE_SOFT;
extern const Palette PALETTE_WHITE;
