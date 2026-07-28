import React, { useContext } from 'react';
import { View } from 'react-native';

import { BLEContext } from '../BLEProvider';

// Zones
import ConnectionBanner from '../components/status/ConnectionBanner';

// Hero
import HeroGauge from '../components/hero/HeroGauge';

// Controls
import TempWheel from '../components/controls/TempWheel';

// Common UI
import ScreenContainer from '../components/common/ScreenContainer';
import Section from '../components/common/Section';
import ControlButton from '../components/common/ControlButton';

export default function HomeScreen() {
  const {
    found,
    connected,
    currentTemp,
    currentPWM,
    device,
    setTargetTemp,
    setMode
  } = useContext(BLEContext);

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
          {/* Target Temp */}
          <Section title="Set Target Temp">
            <TempWheel
              device={device}
              onChange={setTargetTemp}
            />
          </Section>
        </>
      )}

      {/* SYSTEM ZONE (empty for now) */}
      {/* Future: FirmwareInfo, DebugPanel, OTA, etc. */}

    </ScreenContainer>
  );
}
