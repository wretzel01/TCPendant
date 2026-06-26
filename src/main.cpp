#include <Arduino.h>
#include "thermal_control/thermal_control.h"

float targetTemp = 35.0;
float hysteresis = 1.0;

void setup() {
    Serial.begin(115200);
    ThermalControl::init(2, 3);
}

void loop() {
    ThermalControl::loop(targetTemp, hysteresis);
}
