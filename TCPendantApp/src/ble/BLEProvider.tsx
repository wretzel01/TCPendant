import React, { createContext, useEffect, useRef, useState } from "react";
import { PermissionsAndroid } from "react-native";

import {
  scanForPendant,
  subscribeTelemetry,
  stopScan,
} from "../ble";

import {
  setTargetTemp,
  setMode,
  setLEDColor,
  setLEDAnimation,
  setLEDTheme,
  setLEDBrightness,
} from "../ble/bleCommands";

export const BLEContext = createContext(null);

export function BLEProvider({ children }) {
  const deviceRef = useRef(null);
  const telemetrySubRef = useRef(null);

  const [connected, setConnected] = useState(false);
  const [currentTemp, setCurrentTemp] = useState(null);
  const [currentPWM, setCurrentPWM] = useState(null);

  // ⭐ NEW — battery telemetry
  const [batteryPercent, setBatteryPercent] = useState(null);
  const [batteryVoltage, setBatteryVoltage] = useState(null);
  const [batteryCurrent, setBatteryCurrent] = useState(null);

  useEffect(() => {
    PermissionsAndroid.requestMultiple([
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
    ]);
  }, []);

  const startScanAndAttach = () => {
    scanForPendant(async (d) => {
      deviceRef.current = d;
      setConnected(true);

      telemetrySubRef.current = await subscribeTelemetry(d, (pkt) => {
        console.log("[BLE] Telemetry:", pkt);

        // Thermal
        setCurrentTemp(pkt.temp);
        setCurrentPWM(pkt.pwm);

        // ⭐ Battery
        setBatteryPercent(pkt.batteryPercent);
        setBatteryVoltage(pkt.batteryVoltage);
        setBatteryCurrent(pkt.batteryCurrent);
      });

      d.onDisconnected(() => {
        console.log("[BLE] Disconnected");

        setConnected(false);
        deviceRef.current = null;
        telemetrySubRef.current?.remove?.();

        startScanAndAttach();
      });
    });
  };

  useEffect(() => {
    startScanAndAttach();

    return () => {
      stopScan();
      telemetrySubRef.current?.remove?.();
    };
  }, []);

  return (
    <BLEContext.Provider
      value={{
        connected,
        currentTemp,
        currentPWM,

        // ⭐ Battery exposed to app
        batteryPercent,
        batteryVoltage,
        batteryCurrent,

        device: deviceRef.current,
        setTargetTemp,
        setMode,
        setLEDColor,
        setLEDAnimation,
        setLEDTheme,
        setLEDBrightness,
      }}
    >
      {children}
    </BLEContext.Provider>
  );
}
