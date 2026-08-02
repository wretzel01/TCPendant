#pragma once

// High-level battery API for the rest of the firmware.
// Now a safe placeholder until MAX17048 is integrated.

void  batteryMonitorInit();
float getBatteryVoltage();     // Volts
float getBatteryCurrent();     // mA
int   getBatteryPercent();     // 0–100%
