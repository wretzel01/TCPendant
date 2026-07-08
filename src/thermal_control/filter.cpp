#include "filter.h"
#include <math.h>

namespace Filter {

    static float alpha = 0.1f;       // default smoothing factor
    static float lastValue = NAN;    // internal filtered state

    // ---------------------------------------------------------
    // Initialize filter
    // ---------------------------------------------------------
    void init(float a) {
        alpha = constrain(a, 0.0f, 1.0f);
        lastValue = NAN;
    }

    // ---------------------------------------------------------
    // Apply exponential smoothing
    // ---------------------------------------------------------
    float apply(float newValue) {
        if (isnan(lastValue)) {
            lastValue = newValue;   // first sample initializes filter
            return lastValue;
        }

        lastValue = alpha * newValue + (1.0f - alpha) * lastValue;
        return lastValue;
    }

    // ---------------------------------------------------------
    // Reset filter state
    // ---------------------------------------------------------
    void reset() {
        lastValue = NAN;
    }

    // ---------------------------------------------------------
    // Accessors
    // ---------------------------------------------------------
    float getLast() {
        return lastValue;
    }

    void setAlpha(float a) {
        alpha = constrain(a, 0.0f, 1.0f);
    }

    float getAlpha() {
        return alpha;
    }

}
