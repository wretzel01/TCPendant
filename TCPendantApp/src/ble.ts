import { BleManager } from 'react-native-ble-plx';
import { encode as btoa, decode as atob } from 'base-64';

export const SERVICE_UUID = "1234";
export const TARGET_TEMP_UUID = "1235";
export const MODE_UUID = "1236";
export const CUR_TEMP_UUID = "1237";
export const CUR_PWM_UUID = "1238";

export const manager = new BleManager();

export async function connectToPendant(device) {
  console.log("Connecting to TCPendant...");
  const connected = await device.connect();
  console.log("Connected!");
  const discovered = await connected.discoverAllServicesAndCharacteristics();
  console.log("Services discovered!");
  return discovered;
}

export async function setTargetTemp(device, temp: number) {
  console.log("setTargetTemp write:", temp);
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    TARGET_TEMP_UUID,
    btoa(String(temp))          // <-- IMPORTANT: Base64 of "35" / "40"
  );
}

export async function setMode(device, mode: number) {
  console.log("setMode write:", mode);
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    MODE_UUID,
    btoa(String.fromCharCode(mode))
  );
}

export function subscribeToTelemetry(device, onTemp, onPWM) {
  device.monitorCharacteristicForService(
    SERVICE_UUID,
    CUR_TEMP_UUID,
    (error, characteristic) => {
      if (error) return console.log("Temp notify error:", error);
      try {
        const decoded = atob(characteristic.value); // Base64 → ASCII
        console.log("Temp notify raw:", decoded);
        onTemp(parseFloat(decoded));
      } catch (e) {
        console.log("Temp decode error:", e);
      }
    }
  );

  device.monitorCharacteristicForService(
    SERVICE_UUID,
    CUR_PWM_UUID,
    (error, characteristic) => {
      if (error) return console.log("PWM notify error:", error);
      try {
        const decoded = atob(characteristic.value);
        console.log("PWM notify raw:", decoded);
        onPWM(decoded.charCodeAt(0));
      } catch (e) {
        console.log("PWM decode error:", e);
      }
    }
  );
}
