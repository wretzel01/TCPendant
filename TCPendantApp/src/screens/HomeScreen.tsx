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

// Common UI
import ScreenContainer from '../components/common/ScreenContainer';
import Section from '../components/common/Section';

export default function HomeScreen() {
  const ble = useContext(BLEContext);

  // ⭐ Prevent crash if context is null
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
    device,
    setTargetTemp,
  } = ble;

  return (
    <ScreenContainer>

      {/* STATUS ZONE */}
      <ConnectionBanner connected={connected} />

      {/* HERO ZONE */}
      {connected && (
        <View style={{ alignItems: 'center' }}>
          <HeroGauge temp={currentTemp} pwm={currentPWM} />
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

          {/* ⭐ LED CONTROL PANEL */}
          <LEDControlsPanel />
        </>
      )}

    </ScreenContainer>
  );
}
