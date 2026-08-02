import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDColorControls({ device, setLEDColor }) {
  return (
    <View style={{ flexDirection: 'row', justifyContent: 'space-around' }}>
      <ControlButton label="Red" onPress={() => setLEDColor(device, 255, 0, 0)} />
      <ControlButton label="Green" onPress={() => setLEDColor(device, 0, 255, 0)} />
      <ControlButton label="Blue" onPress={() => setLEDColor(device, 0, 0, 255)} />
    </View>
  );
}
