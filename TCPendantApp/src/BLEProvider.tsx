import React, { createContext, useEffect, useRef, useState } from 'react';
import { PermissionsAndroid } from 'react-native';
import { manager, connectToPendant, subscribeToTelemetry, setTargetTemp, setMode } from './ble';

export const BLEContext = createContext(null);

export function BLEProvider({ children }) {
  const deviceRef = useRef(null);

  const [found, setFound] = useState(false);
  const [connected, setConnected] = useState(false);
  const [currentTemp, setCurrentTemp] = useState(null);
  const [currentPWM, setCurrentPWM] = useState(null);

  // Permissions
  useEffect(() => {
    PermissionsAndroid.requestMultiple([
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
    ]);
  }, []);

  // Scan + connect + subscribe
  useEffect(() => {
    const subscription = manager.onStateChange((state) => {
      if (state === 'PoweredOn') {
        manager.startDeviceScan(null, null, async (error, device) => {
          if (error) return;

          if (device?.name === 'TCPendant') {
            setFound(true);
            manager.stopDeviceScan();

            const connectedDevice = await connectToPendant(device);
            deviceRef.current = connectedDevice;
            setConnected(true);

            subscribeToTelemetry(
              connectedDevice,
              (temp) => setCurrentTemp(temp),
              (pwm) => setCurrentPWM(pwm)
            );

            connectedDevice.onDisconnected(async () => {
              try {
                const newDevice = await connectedDevice.connect();
                await newDevice.discoverAllServicesAndCharacteristics();

                deviceRef.current = newDevice;

                subscribeToTelemetry(
                  newDevice,
                  (temp) => setCurrentTemp(temp),
                  (pwm) => setCurrentPWM(pwm)
                );

                setConnected(true);
              } catch {
                setConnected(false);
              }
            });
          }
        });
      }
    }, true);

    return () => subscription.remove();
  }, []);

  return (
    <BLEContext.Provider value={{
      found,
      connected,
      currentTemp,
      currentPWM,
      device: deviceRef.current,
      setTargetTemp,
      setMode
    }}>
      {children}
    </BLEContext.Provider>
  );
}
