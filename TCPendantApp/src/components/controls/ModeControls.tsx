import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function ModeControls({ device, setMode }) {
  return (
    <View style={{ flexDirection: 'row', justifyContent: 'space-around' }}>
      <ControlButton label="Off" onPress={() => setMode(device, 0)} />
      <ControlButton label="Normal" onPress={() => setMode(device, 1)} />
      <ControlButton label="High" onPress={() => setMode(device, 2)} />
    </View>
  );
}
