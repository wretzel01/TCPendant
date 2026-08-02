import { manager } from "./bleManager";

const SERVICE_UUID = "1234";
const KICK_UUID    = "1244";

export function scanForPendant(onFound) {
  manager.startDeviceScan(null, null, async (error, device) => {
    if (error) return;

    if (device?.name === "TCPendant") {
      console.log("[BLE] Found device:", device.id, device.name);

      // stop scan immediately
      manager.stopDeviceScan();

      let d;
      try {
        d = await manager.connectToDevice(device.id, { autoConnect: false });
        console.log("[BLE] Connected:", d.id);
      } catch (e) {
        console.log("[BLE] Connect failed:", e);
        return;
      }

      try {
        await d.discoverAllServicesAndCharacteristics();
        console.log("[BLE] Discovered services");
      } catch (e) {
        console.log("[BLE] Discovery failed:", e);
      }

      try {
        const kickValue = btoa(String.fromCharCode(1));
        await manager.writeCharacteristicWithoutResponseForDevice(
          d.id,
          SERVICE_UUID,
          KICK_UUID,
          kickValue
        );
      } catch (e) {
        console.log("[BLE] Kick failed:", e);
      }

      onFound(d);
    }
  });
}

export function stopScan() {
  manager.stopDeviceScan();
}
