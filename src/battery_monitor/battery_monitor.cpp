#include "battery_monitor.h"

// Placeholder filtered values
static float voltageFiltered = 0.0f;
static float currentFiltered = 0.0f;

static constexpr float SMOOTHING = 0.2f;

// Placeholder init — does nothing now
void batteryMonitorInit() {
    // No INA219, no I2C, no initialization needed
}

// Placeholder voltage — stable, safe, no stalls
float getBatteryVoltage() {
    float v = 0.0f;  // placeholder
    voltageFiltered = SMOOTHING * voltageFiltered + (1.0f - SMOOTHING) * v;
    return voltageFiltered;
}

// Placeholder current — stable, safe, no stalls
float getBatteryCurrent() {
    float c = 0.0f;  // placeholder
    currentFiltered = SMOOTHING * currentFiltered + (1.0f - SMOOTHING) * c;
    return currentFiltered;
}

// Placeholder percent — always 100 for now
int getBatteryPercent() {
    return 100;
}
