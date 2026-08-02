import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDBrightnessControls({ device, setLEDBrightness }) {
  return (
    <View style={{ flexDirection: 'row', justifyContent: 'space-around' }}>
      <ControlButton label="Low" onPress={() => setLEDBrightness(device, 40)} />
      <ControlButton label="Med" onPress={() => setLEDBrightness(device, 120)} />
      <ControlButton label="High" onPress={() => setLEDBrightness(device, 255)} />
    </View>
  );
}
