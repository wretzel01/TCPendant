#include "light_control.h"
#include <Adafruit_NeoPixel.h>
#include "palette.h"

static const int LED_COUNT = 1;
static Adafruit_NeoPixel strip(LED_COUNT, 4, NEO_GRB + NEO_KHZ800);

// Raw BLE state
static Color rawColor = COLOR_AMBER;
static uint8_t rawBrightness = 255;
static AnimationId rawAnimation = ANIM_STATIC;

// Theme state
static ThemeId currentTheme = THEME_AMBER;

// Mode flag
static bool useTheme = true;

void LightControl::init(int pin) {
    strip.setPin(pin);
    strip.begin();
    strip.show();
}

void LightControl::setColor(uint8_t r, uint8_t g, uint8_t b) {
    rawColor = {r, g, b};
    useTheme = false;
}

void LightControl::setBrightness(uint8_t b) {
    rawBrightness = b;
    useTheme = false;
}

void LightControl::setAnimation(AnimationId id) {
    rawAnimation = id;
    useTheme = false;
}

void LightControl::setTheme(ThemeId id) {
    if (id == THEME_NONE) {
        useTheme = false;
        return;
    }
    currentTheme = id;
    useTheme = true;
}

void LightControl::loop() {

    Color base;
    AnimationId anim;
    float brightnessFactor;

    if (useTheme) {
        const Theme& t = getTheme(currentTheme);
        base = t.base;
        anim = t.animation;   // <-- use theme animation
        brightnessFactor = t.brightness / 255.0f;
    } else {
        base = rawColor;
        anim = rawAnimation;  // <-- use raw animation from BLE
        brightnessFactor = rawBrightness / 255.0f;
    }

    base = scale(base, brightnessFactor);

    Color final = Animations::run(anim, base);

    strip.setPixelColor(0, strip.Color(final.r, final.g, final.b));
    strip.show();
}
