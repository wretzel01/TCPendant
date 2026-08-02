import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDAnimationControls({ device, setLEDAnimation }) {
  return (
    <View style={{ flexDirection: 'row', justifyContent: 'space-around' }}>
      <ControlButton label="Static" onPress={() => setLEDAnimation(device, 0)} />
      <ControlButton label="Pulse" onPress={() => setLEDAnimation(device, 1)} />
      <ControlButton label="Rainbow" onPress={() => setLEDAnimation(device, 2)} />
    </View>
  );
}
