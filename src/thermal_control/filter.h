#ifndef FILTER_H
#define FILTER_H

#include <Arduino.h>

namespace Filter {

    // Initialize filter with a user-defined smoothing factor (0.0–1.0)
    void init(float alpha);

    // Apply exponential smoothing to a new sample
    float apply(float newValue);

    // Reset filter state (useful when switching modes)
    void reset();

    // Get last filtered value
    float getLast();

    // Change smoothing factor at runtime
    void setAlpha(float alpha);

    // Retrieve current smoothing factor
    float getAlpha();
}

#endif
