#pragma once
#include <stdint.h>

// ---------------------------------------------
// Basic RGB color struct
// ---------------------------------------------
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// ---------------------------------------------
// Named colors (extern — defined in colors.cpp)
// ---------------------------------------------
extern const Color COLOR_AMBER;
extern const Color COLOR_GOLD;
extern const Color COLOR_ORANGE;
extern const Color COLOR_RED;
extern const Color COLOR_GREEN;
extern const Color COLOR_BLUE;
extern const Color COLOR_WHITE;
extern const Color COLOR_SOFT_WHITE;
extern const Color COLOR_ICE_BLUE;

// ---------------------------------------------
// Utility functions
// ---------------------------------------------

// Scale brightness (0.0–1.0)
Color scale(const Color& c, float factor);

// Blend two colors (0.0–1.0)
Color blend(const Color& a, const Color& b, float t);

// Apply a warm/cool tint (for thermal effects)
Color tint(const Color& base, float warmth);
