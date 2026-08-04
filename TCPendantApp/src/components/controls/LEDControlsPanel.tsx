import React, { useContext } from 'react';
import { View } from 'react-native';

import { BLEContext } from '../../ble/BLEProvider';
import Section from '../common/Section';

import LEDColorControls from './LEDColorControls';
import LEDBrightnessControls from './LEDBrightnessControls';
import LEDAnimationControls from './LEDAnimationControls';
import LEDThemeControls from './LEDThemeControls';
import { setLEDTheme } from '../../ble';

export default function LEDControlsPanel() {
  const {
    device,
    setLEDColor,
    setLEDTheme,
    setLEDBrightness,
    setLEDAnimation,
  } = useContext(BLEContext);

  return (
    <View>

      <Section title="LED Color">
        <LEDColorControls device={device} setLEDColor={setLEDColor} />
      </Section>

      <Section title="Brightness">
        <LEDBrightnessControls device={device} setLEDBrightness={setLEDBrightness} />
      </Section>

      <Section title="Animations">
        <LEDAnimationControls device={device} setLEDAnimation={setLEDAnimation} />
      </Section>

      <Section title="Themes">
        <LEDThemeControls device={device} setLEDTheme={setLEDTheme} />
      </Section>

    </View>
  );
}
