/*
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 4       // DIN connected to GPIO 4
#define LED_COUNT 1     // You have one LED

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(500);

  // Test sequence
  strip.setPixelColor(0, strip.Color(255, 0, 0)); // Red
  strip.show();
  delay(1000);

  strip.setPixelColor(0, strip.Color(0, 255, 0)); // Green
  strip.show();
  delay(1000);

  strip.setPixelColor(0, strip.Color(0, 0, 255)); // Blue
  strip.show();
  delay(1000);

  strip.setPixelColor(0, strip.Color(255, 255, 255)); // White
  strip.show();
  delay(1000);

  strip.clear();
  strip.show();
}

void loop() {
  // Nothing here — one‑shot test
}
*/
