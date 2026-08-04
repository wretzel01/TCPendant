import { Buffer } from "buffer";
import { SERVICE_UUID, STATE_SYNC_UUID } from "./bleUUIDs";

export function parseTelemetry(base64) {
  const buf = Buffer.from(base64, "base64");

  // Must be at least 5 bytes for temp + pwm
  if (buf.length < 5) return null;

  const pkt = {
    temp: buf.readFloatLE(0),
    pwm: buf.readUInt8(4),
  };

  // BatteryVoltage (float) requires bytes 8–11
  if (buf.length >= 12) {
    pkt.batteryVoltage = buf.readFloatLE(8);
  }

  // BatteryPercent (uint8) requires byte 12
  if (buf.length >= 13) {
    pkt.batteryPercent = buf.readUInt8(12);
  }

  // BatteryCurrent (float) requires bytes 13–16
  if (buf.length >= 17) {
    pkt.batteryCurrent = buf.readFloatLE(13);
  }

  // LED R/G/B require bytes 17–19
  if (buf.length >= 20) {
    pkt.ledR = buf.readUInt8(17);
    pkt.ledG = buf.readUInt8(18);
    pkt.ledB = buf.readUInt8(19);
  }

  return pkt;
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
