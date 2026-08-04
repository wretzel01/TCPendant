import React, { useContext } from 'react';
import { View, Text } from 'react-native';

import { BLEContext } from '../ble/BLEProvider';

// Zones
import ConnectionBanner from '../components/status/ConnectionBanner';

// Hero
import HeroGauge from '../components/hero/HeroGauge';

// Controls
import TempWheel from '../components/controls/TempWheel';
import LEDControlsPanel from '../components/controls/LEDControlsPanel';
import ModeControls from '../components/controls/ModeControls';

// Common UI
import ScreenContainer from '../components/common/ScreenContainer';
import Section from '../components/common/Section';

export default function HomeScreen() {
  const ble = useContext(BLEContext);

  if (!ble) {
    return (
      <ScreenContainer>
        <Text>Initializing BLE…</Text>
      </ScreenContainer>
    );
  }

  const {
    connected,
    currentTemp,
    currentPWM,

    // ⭐ Battery fields
    batteryPercent,
    batteryVoltage,
    batteryCurrent,

    device,
    setTargetTemp,
    setMode,
  } = ble;

  // ⭐ Safe formatting
  const batteryPctText =
    batteryPercent !== null && batteryPercent !== undefined
      ? `${batteryPercent}%`
      : '—';

  const batteryVoltText =
    batteryVoltage !== null && batteryVoltage !== undefined
      ? `${batteryVoltage.toFixed(2)}V`
      : '';

  return (
    <ScreenContainer>

      {/* STATUS ZONE */}
      <ConnectionBanner connected={connected} />

      {/* HERO ZONE */}
      {connected && (
        <View style={{ alignItems: 'center' }}>
          <HeroGauge temp={currentTemp} pwm={currentPWM} />

          {/* ⭐ Battery Display (SAFE) */}
          <Text style={{ marginTop: 12, fontSize: 18, color: 'white' }}>
            Battery: {batteryPctText}
          </Text>
        </View>
      )}

      {/* CONTROL ZONE */}
      {connected && (
        <>
          <Section title="Set Target Temp">
            <TempWheel
              device={device}
              onChange={setTargetTemp}
            />
          </Section>

          <Section title="Mode">
            <ModeControls device={device} setMode={setMode} />
          </Section>

          <LEDControlsPanel />
        </>
      )}
    </ScreenContainer>
  );
}
