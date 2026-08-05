import React, { useContext } from 'react';
import { View, StyleSheet } from 'react-native';
import { BLEContext } from '../../ble/BLEProvider';
import Section from '../common/Section';
import LEDColorControls from './LEDColorControls';
import LEDBrightnessControls from './LEDBrightnessControls';
import LEDAnimationControls from './LEDAnimationControls';
import LEDThemeControls from './LEDThemeControls';

export default function LEDControlsPanel() {
  const {
    device,
    setLEDColor,
    setLEDTheme,
    setLEDBrightness,
    setLEDAnimation,
  } = useContext(BLEContext);

  return (
    <View style={styles.panelContainer}>
      <View style={styles.card}>
        <Section title="LED Color">
          <LEDColorControls device={device} setLEDColor={setLEDColor} />
        </Section>
      </View>

      <View style={styles.card}>
        <Section title="Brightness">
          <LEDBrightnessControls device={device} setLEDBrightness={setLEDBrightness} />
        </Section>
      </View>

      <View style={styles.card}>
        <Section title="Animations">
          <LEDAnimationControls device={device} setLEDAnimation={setLEDAnimation} />
        </Section>
      </View>

      <View style={styles.card}>
        <Section title="Themes">
          <LEDThemeControls device={device} setLEDTheme={setLEDTheme} />
        </Section>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  panelContainer: {
    gap: 16,
    marginTop: 8,
  },
  card: {
    backgroundColor: 'rgba(255, 255, 255, 0.05)',
    borderRadius: 16,
    padding: 16,
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.08)',
  },
});