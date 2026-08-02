#include "animations.h"
#include <Arduino.h>

// ---------------------------------------------
// Global animation state (one LED = one state)
// ---------------------------------------------
static AnimationState animState;

// ---------------------------------------------
// Animation router
// ---------------------------------------------
Color Animations::run(AnimationId id, const Color& base) {
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
// Breathe animation (smooth sinusoidal)
// ---------------------------------------------
Color Animations::breathe(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 20) return base;
    s.lastUpdate = now;

    s.phase += 0.03f;
    float intensity = (sin(s.phase) + 1.0f) * 0.5f;  // 0–1
    intensity = intensity * 0.6f + 0.2f;            // soften

    return scale(base, intensity);
}

// ---------------------------------------------
// Pulse animation (sharp rise, slow fall)
// ---------------------------------------------
Color Animations::pulse(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 20) return base;
    s.lastUpdate = now;

    s.phase += 0.05f;

    float t = fmod(s.phase, 1.0f);
    float intensity = (t < 0.2f)
        ? (t / 0.2f)            // fast rise
        : (1.0f - (t - 0.2f) / 0.8f); // slow fall

    return scale(base, intensity);
}

// ---------------------------------------------
// Flicker animation (random fire-like jitter)
// ---------------------------------------------
Color Animations::flicker(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 30) return base;
    s.lastUpdate = now;

    float intensity = 0.7f + (random(-30, 30) / 100.0f); // 0.4–1.0
    if (intensity < 0.4f) intensity = 0.4f;
    if (intensity > 1.0f) intensity = 1.0f;

    return scale(base, intensity);
}

// ---------------------------------------------
// Twinkle animation (random sparkle bursts)
// ---------------------------------------------
Color Animations::twinkle(const Color& base, AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 40) return base;
    s.lastUpdate = now;

    float t = random(0, 100) / 100.0f; // 0–1
    float intensity = (t > 0.85f) ? 1.0f : 0.3f; // occasional sparkle

    return scale(base, intensity);
}

// ---------------------------------------------
// Rainbow animation (HSV-like cycling)
// ---------------------------------------------
Color Animations::rainbow(AnimationState& s) {
    uint32_t now = millis();
    if (now - s.lastUpdate < 20) return COLOR_RED;
    s.lastUpdate = now;

    s.phase += 0.02f;
    float t = fmod(s.phase, 1.0f);

    // Simple HSV → RGB approximation
    uint8_t r = (uint8_t)(sin(t * 6.28f) * 127 + 128);
    uint8_t g = (uint8_t)(sin((t + 0.33f) * 6.28f) * 127 + 128);
    uint8_t b = (uint8_t)(sin((t + 0.66f) * 6.28f) * 127 + 128);

    return {r, g, b};
}
