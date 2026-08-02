import { BleManager } from "react-native-ble-plx";

// ⭐ No restoreState — prevents ghost GATT connections
export const manager = new BleManager();

export async function connect(device) {
  try {
    // ⭐ First attempt — may fail if Android has stale state
    try {
      const d = await manager.connectToDevice(device.id, { autoConnect: false });
      await d.discoverAllServicesAndCharacteristics();
      return d;
    } catch (firstError) {
      console.log("[BLE] First connect attempt failed:", firstError);

      // ⭐ Force disconnect (even if BLE‑PLX thinks it's not connected)
      try {
        await manager.cancelDeviceConnection(device.id);
      } catch (_) {}

      // ⭐ Wait for Android to flush stale GATT state
      await new Promise((resolve) => setTimeout(resolve, 500));

      // ⭐ Second attempt — this one succeeds after ESP32 reboot
      const d = await manager.connectToDevice(device.id, { autoConnect: false });
      await d.discoverAllServicesAndCharacteristics();
      return d;
    }
  } catch (e) {
    console.log("[BLE] connect error:", e, e?.reason);
    return null;
  }
}
