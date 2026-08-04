#pragma once
#include <stdint.h>
#include "colors.h"
#include "palette.h"

// ---------------------------------------------
// Animation IDs
// ---------------------------------------------
enum AnimationId : uint8_t {
    ANIM_NONE = 0,
    ANIM_STATIC = 1,
    ANIM_BREATHE = 2,
    ANIM_PULSE = 3,
    ANIM_FLICKER = 4,
    ANIM_TWINKLE = 5,
    ANIM_RAINBOW = 6
};

// ---------------------------------------------
// Animation state container
// ---------------------------------------------
struct AnimationState {
    uint16_t phase = 0;
    uint32_t lastUpdate = 0;

    uint8_t lastIntensity = 255;     // flicker smoothing
    uint8_t sparkleIntensity = 0;    // twinkle fade-out

    Color lastColor = {0, 0, 0};     // return previous frame
    Color lastPaletteColor;
};

// ---------------------------------------------
// Animation API
// ---------------------------------------------
namespace Animations {
    Color run(AnimationId id, const Color& base);

    Color breathe(const Color& base, AnimationState& s);
    Color pulse(const Color& base, AnimationState& s);
    Color flicker(const Color& base, AnimationState& s);
    Color twinkle(const Color& base, AnimationState& s);
    Color rainbow(AnimationState& s);

    void setPalette(const Palette* pal);
}

