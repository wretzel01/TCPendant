#include "animations.h"
#include <Arduino.h>

// ---------------------------------------------
// Global animation state
// ---------------------------------------------
static AnimationState animState;
static AnimationId currentAnim = ANIM_NONE;

// ---------------------------------------------
// Reset animation state
// ---------------------------------------------
static void resetState(AnimationState& s) {
    s.phase = 0;
    s.lastUpdate = 0;
}

// ---------------------------------------------
// Animation router
// ---------------------------------------------
Color Animations::run(AnimationId id, const Color& base) {

    if (id != currentAnim) {
        resetState(animState);
        currentAnim = id;
    }

    switch (id) {
        case ANIM_STATIC:   return base;
        case ANIM_BREATHE:  return breathe(base, animState);
        case ANIM_PULSE:    return pulse(base, animState);
        case ANIM_FLICKER:  return flicker(base, animState);
        case ANIM_TWINKLE:  return twinkle(base, animState);
        case ANIM_RAINBOW:  return rainbow(animState);
        default:            return base;
    }
}

// ---------------------------------------------
// Breathe (AMPLIFIED)
// ---------------------------------------------
Color Animations::breathe(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    s.lastUpdate = now;

    // VERY slow phase increment
    s.phase = (s.phase + 1) % 2048;   // 2048 steps = ~5 seconds

    float x = s.phase / 2048.0f;

    // soft breathing curve
    float intensity = (sin(x * PI * 2) + 1.0f) * 0.5f;  // 0 → 1
    intensity = pow(intensity, 1.8f);                   // soften

    return {
        (uint8_t)(base.r * intensity),
        (uint8_t)(base.g * intensity),
        (uint8_t)(base.b * intensity)
    };
}

// ---------------------------------------------
// Pulse (AMPLIFIED)
// ---------------------------------------------
Color Animations::pulse(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    s.lastUpdate = now;

    // 1000 steps = ~1 second fade
    s.phase = (s.phase + 1) % 1500;

    float x = s.phase / 1500.0f;

    float intensity;

    if (s.phase == 0) {
        // instant flash
        intensity = 1.0f;
    } else {
        // smooth fade-out
        intensity = 1.0f - x;
    }

    return {
        (uint8_t)(base.r * intensity),
        (uint8_t)(base.g * intensity),
        (uint8_t)(base.b * intensity)
    };
}

// ---------------------------------------------
// Flicker (AMPLIFIED)
// ---------------------------------------------
Color Animations::flicker(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    s.lastUpdate = now;

    // Random trigger: 10% chance per frame
    if (random(0, 100) < 10) {
        s.sparkleIntensity = 128;   // 50% brightness
    }

    // Fade from 50% → 0%
    if (s.sparkleIntensity > 0) {
        s.sparkleIntensity -= 4;    // adjust fade speed here
        if (s.sparkleIntensity < 0) s.sparkleIntensity = 0;
    }

    float intensity = s.sparkleIntensity / 255.0f;  // 0.5 → 0.0

    return {
        (uint8_t)(base.r * intensity),
        (uint8_t)(base.g * intensity),
        (uint8_t)(base.b * intensity)
    };
}
// ---------------------------------------------
// Twinkle (AMPLIFIED)
// ---------------------------------------------
Color Animations::twinkle(const Color& base, AnimationState& s) {
    uint32_t now = millis();

    // Slower update rate (slow motion)
    if (now - s.lastUpdate < 80) return s.lastColor;
    s.lastUpdate = now;

    // Same chaotic randomness as flicker, but slightly narrower
    int intensity = random(0, 200);   // chaotic but softer

    Color out = {
        (uint8_t)((base.r * intensity) >> 8),
        (uint8_t)((base.g * intensity) >> 8),
        (uint8_t)((base.b * intensity) >> 8)
    };

    s.lastColor = out;
    return out;
}

// ---------------------------------------------
// Rainbow (unchanged — already visible)
// ---------------------------------------------
Color Animations::rainbow(AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 15) return {255, 0, 0};
    s.lastUpdate = now;

    s.phase = (s.phase + 4) % 768;

    int section = s.phase / 256;
    int offset  = s.phase % 256;

    uint8_t r, g, b;

    switch (section) {
        case 0: r = 255 - offset; g = offset;       b = 0;         break;
        case 1: r = 0;            g = 255 - offset; b = offset;    break;
        case 2: r = offset;       g = 0;            b = 255 - offset; break;
    }

    return {r, g, b};
}
