#pragma once

namespace BatteryMonitor {

    void init(int sdaPin, int sclPin);
    void loop();

    float getVoltage();
    float getCurrent();
    int   getPercent();

}
