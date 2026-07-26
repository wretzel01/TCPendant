#include "ble_connect.h"

#include "ble_init.h"
#include "ble_telemetry.h"

namespace BLEConnect {

    // ---------------------------------------------------------
    // Initialize BLE subsystem
    // ---------------------------------------------------------
    void init() {
        BLEInit::setup();
    }

    // ---------------------------------------------------------
    // Periodic BLE work (telemetry scheduler)
    // ---------------------------------------------------------
    void loop() {
        BLETelemetry::loop();
    }

}
