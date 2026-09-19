#include "thermistor.h"
#include <math.h>

namespace Thermistor {

    static int thermPin = 2;

    const float SERIES_RESISTOR      = 10000.0;
    const float NOMINAL_RESISTANCE   = 10000.0;
    const float NOMINAL_TEMPERATURE  = 25.0;
    const float BETA_COEFFICIENT     = 3950.0;

    const float FILTER_ALPHA = 0.10;
    static float filteredTemp = NAN;

    void init(int pin) {
        thermPin = pin;
        pinMode(thermPin, INPUT);
    }

    int readADC() {
        return analogRead(thermPin);
    }

    float readRawCelsius() {
        int raw = readADC();

        // ADC ratio (0.0–1.0)
        float adcRatio = (float)raw / 4095.0f;
        if (adcRatio <= 0.0f) return -273.15f;

        // Correct resistance formula for:
        // 3.3V → 10k → ADC → Thermistor → GND
        float resistance = (adcRatio * SERIES_RESISTOR) / (1.0f - adcRatio);

        float steinhart = resistance / NOMINAL_RESISTANCE;
        steinhart = log(steinhart);
        steinhart /= BETA_COEFFICIENT;
        steinhart += 1.0f / (NOMINAL_TEMPERATURE + 273.15f);
        steinhart = 1.0f / steinhart;

        return steinhart - 273.15f;
    }

    bool isFault(int rawADC) {
        return (rawADC < 10 || rawADC > 4080);
    }

    float readCelsius() {
        float rawTemp = readRawCelsius();

        if (isnan(filteredTemp)) {
            filteredTemp = rawTemp;
        }

        filteredTemp = FILTER_ALPHA * rawTemp +
                       (1.0f - FILTER_ALPHA) * filteredTemp;

        return filteredTemp;
    }

}
