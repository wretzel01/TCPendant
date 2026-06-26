#include "thermistor.h"
#include <math.h>

namespace Thermistor {

    // --- Configurable constants ---
    static int thermPin = 2;

    const float SERIES_RESISTOR      = 10000.0;
    const float NOMINAL_RESISTANCE   = 10000.0;
    const float NOMINAL_TEMPERATURE  = 25.0;
    const float BETA_COEFFICIENT     = 3950.0;

    // Smoothing factor (0.0–1.0)
    const float FILTER_ALPHA = 0.10;

    // Internal filtered temperature
    static float filteredTemp = NAN;


    // ---------------------------------------------------------
    // Initialization
    // ---------------------------------------------------------
    void init(int pin) {
        thermPin = pin;
        pinMode(thermPin, INPUT);
    }


    // ---------------------------------------------------------
    // Raw ADC read
    // ---------------------------------------------------------
    int readADC() {
        return analogRead(thermPin);
    }


    // ---------------------------------------------------------
    // Convert ADC → °C (no filtering)
    // ---------------------------------------------------------
    float readRawCelsius() {
        int raw = readADC();

        float voltageRatio = (float)raw / 4095.0;
        if (voltageRatio <= 0.0) return -273.15;  // avoid div-by-zero

        float resistance = SERIES_RESISTOR * (1.0 / voltageRatio - 1.0);

        float steinhart = resistance / NOMINAL_RESISTANCE;
        steinhart = log(steinhart);
        steinhart /= BETA_COEFFICIENT;
        steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
        steinhart = 1.0 / steinhart;

        return steinhart - 273.15;
    }


    // ---------------------------------------------------------
    // Fault detection (open/short)
    // ---------------------------------------------------------
    bool isFault(int rawADC) {
        return (rawADC < 10 || rawADC > 4080);
    }


    // ---------------------------------------------------------
    // Filtered temperature read
    // ---------------------------------------------------------
    float readCelsius() {
        float rawTemp = readRawCelsius();

        if (isnan(filteredTemp)) {
            filteredTemp = rawTemp;  // initialize filter
        }

        filteredTemp = (FILTER_ALPHA * rawTemp) +
                       ((1.0 - FILTER_ALPHA) * filteredTemp);

        return filteredTemp;
    }

}
