import { Buffer } from "buffer";
import { SERVICE_UUID, STATE_SYNC_UUID } from "./bleUUIDs";

export function parseTelemetry(base64) {
  const buf = Buffer.from(base64, "base64");
  if (buf.length < 17) return null;

  return {
    temp: buf.readFloatLE(0),
    pwm: buf.readUInt8(4),
  };
}

export async function subscribeTelemetry(device, onPkt) {
  const chars = await device.characteristicsForService(SERVICE_UUID);
  const stateChar = chars.find(
    (c) => c.uuid.toLowerCase() === STATE_SYNC_UUID.toLowerCase()
  );

  if (!stateChar) return null;

  return stateChar.monitor((error, characteristic) => {
    if (error) return;
    const pkt = parseTelemetry(characteristic?.value);
    if (pkt) onPkt(pkt);
  });
}
