import React, { createContext, useEffect, useRef, useState } from "react";
import { PermissionsAndroid } from "react-native";

import {
  manager,
  connectToPendant,
  subscribeToTelemetry,
  setTargetTemp,
  setMode,
  clearSubscriptions,
} from "./ble";

export const BLEContext = createContext(null);

export function BLEProvider({ children }) {
  const deviceRef = useRef(null);

  const [found, setFound] = useState(false);
  const [connected, setConnected] = useState(false);
  const [currentTemp, setCurrentTemp] = useState(null);
  const [currentPWM, setCurrentPWM] = useState(null);

  // -----------------------------
  // Permissions
  // -----------------------------
  useEffect(() => {
    PermissionsAndroid.requestMultiple([
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
    ]);
  }, []);

  // -----------------------------
  // Scan + connect + subscribe
  // -----------------------------
  useEffect(() => {
    const subscription = manager.onStateChange((state) => {
      if (state !== "PoweredOn") return;

      manager.startDeviceScan(null, null, async (error, device) => {
        if (error) return;

        if (device?.name === "TCPendant") {
          console.log("Found TCPendant");
          setFound(true);
          manager.stopDeviceScan();

          // -----------------------------
          // CONNECT with reconnect callback
          // -----------------------------
          const connectedDevice = await connectToPendant(
            device,
            async (newDevice) => {
              console.log("Reconnect callback fired");

              // Kill stale subscriptions BEFORE resubscribing
              clearSubscriptions();

              // Update deviceRef
              deviceRef.current = newDevice;
              setConnected(true);

              // Subscribe to telemetry on NEW device
              await subscribeToTelemetry(newDevice, (pkt) => {
                setCurrentTemp(pkt.temp);
                setCurrentPWM(pkt.pwm);
              });
            }
          );

          // -----------------------------
          // INITIAL CONNECTION
          // -----------------------------
          deviceRef.current = connectedDevice;
          setConnected(true);

          // Kill stale subs from previous app runs
          clearSubscriptions();

          // Subscribe to telemetry on initial device
          await subscribeToTelemetry(connectedDevice, (pkt) => {
            setCurrentTemp(pkt.temp);
            setCurrentPWM(pkt.pwm);
          });
        }
      });
    }, true);

    return () => subscription.remove();
  }, []);

  return (
    <BLEContext.Provider
      value={{
        found,
        connected,
        currentTemp,
        currentPWM,
        device: deviceRef.current,
        setTargetTemp,
        setMode,
      }}
    >
      {children}
    </BLEContext.Provider>
  );
}
