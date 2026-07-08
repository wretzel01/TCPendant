#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

namespace Thermistor {

    // Initialize thermistor on a given ADC pin
    void init(int pin);

    // Read raw ADC value (0–4095)
    int readADC();

    // Convert ADC → Celsius (unfiltered)
    float readRawCelsius();

    // Filtered Celsius reading (exponential smoothing)
    float readCelsius();

    // Basic fault detection (open/short)
    bool isFault(int rawADC);

}

#endif
