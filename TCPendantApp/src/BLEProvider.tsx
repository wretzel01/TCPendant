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

  // ⭐ NEW STATES
  const [connecting, setConnecting] = useState(false);
  const [disconnected, setDisconnected] = useState(false);

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

      // ⭐ Reset states
      setFound(false);
      setConnected(false);
      setConnecting(false);
      setDisconnected(false);

      manager.startDeviceScan(null, null, async (error, device) => {
        if (error) return;

        if (device?.name === "TCPendant") {
          console.log("Found TCPendant");
          setFound(true);
          setConnecting(true);
          manager.stopDeviceScan();

          // -----------------------------
          // CONNECT with reconnect callback
          // -----------------------------
          const connectedDevice = await connectToPendant(
            device,
            async (newDevice) => {
              console.log("Reconnect callback fired");

              clearSubscriptions();

              deviceRef.current = newDevice;
              setConnected(true);
              setConnecting(false);
              setDisconnected(false);

              await subscribeToTelemetry(newDevice, (pkt) => {
                setCurrentTemp(pkt.temp);
                setCurrentPWM(pkt.pwm);
              });

              // ⭐ Listen for disconnects
              newDevice.onDisconnected(() => {
                console.log("Device disconnected");
                setConnected(false);
                setDisconnected(true);
                setConnecting(false);
                deviceRef.current = null;

                // Restart scan automatically
                manager.startDeviceScan(null, null, () => {});
              });
            }
          );

          // -----------------------------
          // INITIAL CONNECTION
          // -----------------------------
          deviceRef.current = connectedDevice;
          setConnected(true);
          setConnecting(false);
          setDisconnected(false);

          clearSubscriptions();

          await subscribeToTelemetry(connectedDevice, (pkt) => {
            setCurrentTemp(pkt.temp);
            setCurrentPWM(pkt.pwm);
          });

          // ⭐ Listen for disconnects
          connectedDevice.onDisconnected(() => {
            console.log("Device disconnected");
            setConnected(false);
            setDisconnected(true);
            setConnecting(false);
            deviceRef.current = null;

            // Restart scan automatically
            manager.startDeviceScan(null, null, () => {});
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
        connecting,
        disconnected,
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
