#pragma once
#include <stdint.h>
#include "colors.h"

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
// (each animation keeps its own phase/timers)
// ---------------------------------------------
struct AnimationState {
    float phase = 0.0f;
    uint32_t lastUpdate = 0;
};

// ---------------------------------------------
// Animation API
// ---------------------------------------------
namespace Animations {

    // Called once per frame
    Color run(AnimationId id, const Color& base);

    // Individual animation functions
    Color breathe(const Color& base, AnimationState& s);
    Color pulse(const Color& base, AnimationState& s);
    Color flicker(const Color& base, AnimationState& s);
    Color twinkle(const Color& base, AnimationState& s);
    Color rainbow(AnimationState& s);
}
