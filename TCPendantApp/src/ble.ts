import { BleManager } from "react-native-ble-plx";
import { Buffer } from "buffer";
import { encode as btoa } from "base-64";

export const SERVICE_UUID      = "00001234-0000-1000-8000-00805f9b34fb";
export const TARGET_TEMP_UUID  = "00001235-0000-1000-8000-00805f9b34fb";
export const MODE_UUID         = "00001236-0000-1000-8000-00805f9b34fb";
export const STATE_SYNC_UUID   = "00001239-0000-1000-8000-00805f9b34fb";

export const manager = new BleManager();

// -----------------------------
// Internal BLE state
// -----------------------------
let activeDevice = null;
let subscriptions = [];
let isConnected = false;

// -----------------------------
// Subscription helpers
// -----------------------------
export function addSubscription(sub) {
  subscriptions.push(sub);
}

export function clearSubscriptions() {
  subscriptions.forEach((s) => {
    try {
      s.remove();
    } catch (e) {
      console.log("Subscription remove error:", e);
    }
  });
  subscriptions = [];
}

// -----------------------------
// Telemetry parsing
// -----------------------------
export function parseTelemetry(base64) {
  const buf = Buffer.from(base64, "base64");

  return {
    temp: buf.readFloatLE(0),
    pwm: buf.readUInt8(4),
    mode: buf.readUInt8(5),
    flags: buf.readUInt16LE(6),
  };
}

// -----------------------------
// Telemetry subscription
// -----------------------------
export async function subscribeToTelemetry(device, onTelemetry) {
  console.log("[APP] Resolving telemetry characteristic...");

  const chars = await device.characteristicsForService(SERVICE_UUID);

  const stateChar = chars.find(
    (c) => c.uuid.toLowerCase() === STATE_SYNC_UUID.toLowerCase()
  );

  if (!stateChar) {
    console.log("[APP] Telemetry characteristic not found");
    return;
  }

  console.log("[APP] Found telemetry characteristic:", stateChar.uuid);

  const sub = stateChar.monitor((error, characteristic) => {
    if (error) {
      console.log("[APP] Telemetry notify error:", error);
      return;
    }

    console.log("[APP] Telemetry callback fired");
    console.log("[APP] Raw value:", characteristic?.value);

    try {
      const packet = parseTelemetry(characteristic.value);
      console.log("[APP] Parsed packet:", packet);
      onTelemetry(packet);
    } catch (e) {
      console.log("[APP] Telemetry decode error:", e);
    }
  });

  addSubscription(sub);
}

// -----------------------------
// Disconnect + Reconnect handling
// -----------------------------
export function attachDisconnectHandler(device, onReconnect) {
  device.onDisconnected(async () => {
    console.log("Pendant disconnected");

    isConnected = false;

    // Remove JS-level subscriptions
    clearSubscriptions();

    // Cancel BLE-plx monitor transaction
    manager.cancelTransaction('telemetry');

    // Force-close GATT
    try {
      await device.cancelConnection();
    } catch (e) {
      console.log("cancelConnection error:", e);
    }

    // Wait for Android BLE stack to fully release GATT
    console.log("Waiting for BLE stack to settle...");
    await new Promise(resolve => setTimeout(resolve, 1500));

    try {
      console.log("Attempting reconnect...");
      const newDevice = await manager.connectToDevice(device.id);

      await newDevice.discoverAllServicesAndCharacteristics();

      activeDevice = newDevice;
      isConnected = true;

      console.log("Reconnect successful");

      onReconnect(newDevice);

    } catch (e) {
      console.log("Reconnect failed:", e);
    }
  });
}

// -----------------------------
// Connect
// -----------------------------
export async function connectToPendant(device, onReconnect) {
  console.log("Connecting to TCPendant...");

  // FIXED: use manager.connectToDevice
  const connected = await manager.connectToDevice(device.id);
  console.log("Connected!");

  await connected.discoverAllServicesAndCharacteristics();
  const services = await connected.services();
  for (const s of services) {
    console.log("[APP] Service:", s.uuid);
    const chars = await s.characteristics();
    for (const c of chars) {
      console.log("   [APP] Char:", c.uuid, "props:", c.properties);
    }
  }

  console.log("Services discovered!");

  activeDevice = connected;
  isConnected = true;

  attachDisconnectHandler(connected, onReconnect);

  return connected;
}

// -----------------------------
// Safe write commands
// -----------------------------
export async function setTargetTemp(device, temp) {
  if (!isConnected) {
    console.log("Write blocked: device not connected");
    return;
  }

  console.log("setTargetTemp write:", temp);
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    TARGET_TEMP_UUID,
    btoa(String(temp))
  );
}

export async function setMode(device, mode) {
  if (!isConnected) {
    console.log("Write blocked: device not connected");
    return;
  }

  console.log("setMode write:", mode);
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    MODE_UUID,
    btoa(String.fromCharCode(mode))
  );
}
