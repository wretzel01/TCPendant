import { manager } from "./bleManager";
import { SERVICE_UUID } from "./bleUUIDs";
import { connect } from "./bleManager";

export async function tryReconnect(onConnected) {
  try {
    const devices = await manager.connectedDevices([SERVICE_UUID]);
    const pendant = devices.find((d) => d.name === "TCPendant");

    if (!pendant) return null;

    const connected = await connect(pendant);
    if (connected) {
      onConnected(connected);
      return connected;
    }

    return null;
  } catch (e) {
    console.log("[BLE] tryReconnect error:", e);
    return null;
  }
}
