import React from 'react';
import { View, Text } from 'react-native';

export default function TelemetryDisplay({ temp, pwm }) {
  return (
    <View style={{ marginTop: 20, alignItems: 'center' }}>
      <Text style={{ color: 'white', fontSize: 18 }}>
        Temp: {temp}
      </Text>
      <Text style={{ color: 'white', fontSize: 18 }}>
        PWM: {pwm}
      </Text>
    </View>
  );
}
