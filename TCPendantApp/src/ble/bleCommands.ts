import { Buffer } from "buffer";
import { encode as btoa } from "base-64";
import {
  SERVICE_UUID,
  TARGET_TEMP_UUID,
  MODE_UUID,
  LED_COLOR_UUID,
  LED_ANIMATION_UUID,
  LED_THEME_UUID,
  LED_BRIGHTNESS_UUID,
} from "./bleUUIDs";

export async function setTargetTemp(device, temp) {
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    TARGET_TEMP_UUID,
    btoa(String(temp))
  );
}

export async function setMode(device, mode) {
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    MODE_UUID,
    btoa(String.fromCharCode(mode))
  );
}

export async function setLEDColor(device, r, g, b) {
  const payload = Buffer.from([r, g, b]).toString("base64");
  await device.writeCharacteristicWithResponseForService(
    SERVICE_UUID,
    LED_COLOR_UUID,
    payload
  );
}
