#include "light_control.h"
#include <Adafruit_NeoPixel.h>

static const int LED_COUNT = 1;
static Adafruit_NeoPixel strip(LED_COUNT, 4, NEO_GRB + NEO_KHZ800);

// Raw BLE state
static Color rawColor = COLOR_AMBER;
static uint8_t rawBrightness = 255;
static AnimationId rawAnimation = ANIM_NONE;

// Theme state
static ThemeId currentTheme = THEME_AMBER;

// Mode flag
static bool useTheme = true;

void LightControl::init(int pin) {
    strip.setPin(pin);
    strip.begin();
    strip.show();
}

// BLE setters DO NOT disable theme
void LightControl::setColor(uint8_t r, uint8_t g, uint8_t b) {
    rawColor = {r, g, b};
}

void LightControl::setBrightness(uint8_t b) {
    rawBrightness = b;
}

void LightControl::setAnimation(AnimationId id) {
    rawAnimation = id;
}

// Theme explicitly controls useTheme
void LightControl::setTheme(ThemeId id) {
    if (id == THEME_NONE) {
        useTheme = false;
        return;
    }

    currentTheme = id;
    useTheme = true;

    // Clear BLE overrides so theme animation can run
    rawAnimation = ANIM_NONE;
    rawColor = COLOR_AMBER;
    rawBrightness = 255;
}

void LightControl::loop() {

    // -----------------------------
    // 1. Start with theme defaults
    // -----------------------------
    Color base;
    float brightnessFactor;

    if (useTheme) {
        const Theme& t = getTheme(currentTheme);
        base = t.base;
        brightnessFactor = t.brightness / 255.0f;
    } else {
        base = rawColor;
        brightnessFactor = rawBrightness / 255.0f;
    }

    // -----------------------------
    // 2. BLE overrides theme color
    // -----------------------------
    if (rawColor.r != COLOR_AMBER.r ||
        rawColor.g != COLOR_AMBER.g ||
        rawColor.b != COLOR_AMBER.b) {
        base = rawColor;
    }

    // -----------------------------
    // 3. BLE overrides theme brightness
    // -----------------------------
    if (rawBrightness != 255) {
        brightnessFactor = rawBrightness / 255.0f;
    }

    // -----------------------------
    // 4. BLE animation ALWAYS overrides theme animation
    // -----------------------------
    AnimationId anim;
    if (rawAnimation != ANIM_NONE) {
        anim = rawAnimation;
    } else if (useTheme) {
        anim = getTheme(currentTheme).animation;
    } else {
        anim = ANIM_STATIC;
    }

    // -----------------------------
    // 5. Run animation
    // -----------------------------

    Color animated = Animations::run(anim, base);

    uint8_t brightness = (uint8_t)(brightnessFactor * 255);

    Color final = {
        (uint8_t)((animated.r * brightness) >> 8),
        (uint8_t)((animated.g * brightness) >> 8),
        (uint8_t)((animated.b * brightness) >> 8)
    };

    strip.setPixelColor(0, strip.Color(final.r, final.g, final.b));
    strip.show();
}
