import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDAnimationControls({ device, setLEDAnimation }) {
  return (
    <View style={{ flexDirection: 'row', flexWrap: 'wrap', justifyContent: 'center' }}>
      <ControlButton label="Static"  onPress={() => setLEDAnimation(device, 1)} />
      <ControlButton label="Breathe" onPress={() => setLEDAnimation(device, 2)} />
      <ControlButton label="Pulse"   onPress={() => setLEDAnimation(device, 3)} />
      <ControlButton label="Flicker" onPress={() => setLEDAnimation(device, 4)} />
      <ControlButton label="Twinkle" onPress={() => setLEDAnimation(device, 5)} />
    </View>
  );
}
