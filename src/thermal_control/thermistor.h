#pragma once
#include <Arduino.h>

namespace Thermistor {

    void init(int pin);

    float readCelsius();          // returns filtered °C
    float readRawCelsius();       // returns unfiltered °C
    int   readADC();              // raw ADC value

    bool  isFault(int rawADC);    // open/short detection
}
