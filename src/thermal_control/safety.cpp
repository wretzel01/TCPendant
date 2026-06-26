#include "safety.h"
#include "thermistor.h"
#include "heater.h"

namespace Safety {

    static float maxTempC = 42.0;
    static bool faultActive = false;
    static const char* faultReason = nullptr;

    // ---------------------------------------------------------
    // Init
    // ---------------------------------------------------------
    void init(float maxSafeTempC) {
        maxTempC = maxSafeTempC;
        faultActive = false;
        faultReason = nullptr;
    }

    // ---------------------------------------------------------
    // Internal helper: set fault
    // ---------------------------------------------------------
    static void setFault(const char* reason) {
        faultActive = true;
        faultReason = reason;
        Heater::off();
        Serial.print("[SAFETY] Fault: ");
        Serial.println(reason);
    }

    // ---------------------------------------------------------
    // Update safety state (call every loop)
    // ---------------------------------------------------------
    void update(float tempC, int rawADC) {
        if (faultActive) {
            // Once in fault, stay there until reset (for now)
            return;
        }

        // Thermistor fault (open/short)
        if (Thermistor::isFault(rawADC)) {
            setFault("Thermistor fault (open/short)");
            return;
        }

        // Over-temperature
        if (tempC > maxTempC) {
            setFault("Over-temperature");
            return;
        }
    }

    // ---------------------------------------------------------
    // External shutdown (manual)
    // ---------------------------------------------------------
    void shutdown(const char* reason) {
        setFault(reason);
    }

    // ---------------------------------------------------------
    // Query fault state
    // ---------------------------------------------------------
    bool isFault() {
        return faultActive;
    }

    const char* getFaultReason() {
        return faultReason ? faultReason : "";
    }

}
