import React from 'react';
import { Text, View } from 'react-native';

export default function HeroPWM({ pwm }) {
  return (
    <View
      style={{
        position: 'absolute',
        bottom: -10,
        right: -50,
        paddingHorizontal: 10,
        paddingVertical: 6,
        backgroundColor: 'rgba(0,0,0,0.35)',
        borderRadius: 8,
      }}
    >
      <Text style={{ color: 'white', fontSize: 16, fontWeight: '600' }}>
        PWM: {pwm ?? '--'}
      </Text>
    </View>
  );
}
