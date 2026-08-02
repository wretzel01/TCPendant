import React, { createContext, useEffect, useRef, useState } from "react";
import { PermissionsAndroid } from "react-native";

import {
  scanForPendant,
  subscribeTelemetry,
  stopScan,
} from "../ble";

export const BLEContext = createContext(null);

export function BLEProvider({ children }) {
  const deviceRef = useRef(null);
  const telemetrySubRef = useRef(null);

  const [connected, setConnected] = useState(false);
  const [currentTemp, setCurrentTemp] = useState(null);
  const [currentPWM, setCurrentPWM] = useState(null);

  useEffect(() => {
    PermissionsAndroid.requestMultiple([
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
    ]);
  }, []);

  const startScanAndAttach = () => {
    scanForPendant(async (d) => {
      // d is already connected + discovered + kicked
      deviceRef.current = d;
      setConnected(true);

      telemetrySubRef.current = await subscribeTelemetry(d, (pkt) => {
        console.log("[BLE] Telemetry:", pkt);
        setCurrentTemp(pkt.temp);
        setCurrentPWM(pkt.pwm);
      });

      d.onDisconnected(() => {
        console.log("[BLE] Disconnected");

        setConnected(false);
        deviceRef.current = null;
        telemetrySubRef.current?.remove?.();

        // just start a fresh scan; scanner will reconnect
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
        device: deviceRef.current,
        setTargetTemp: () => {},
      }}
    >
      {children}
    </BLEContext.Provider>
  );
}
