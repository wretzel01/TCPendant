import React from 'react';
import { View, Text } from 'react-native';

export default function HeroTemp({ temp, size }) {
  const safeTemp =
    typeof temp === 'number' && !isNaN(temp)
      ? temp.toFixed(1)
      : '--.-';

  return (
    <View
      style={{
        position: 'absolute',
        width: size,        // ⭐ REQUIRED
        height: size,       // ⭐ REQUIRED
        justifyContent: 'center',
        alignItems: 'center',
      }}
    >
      <Text
        style={{
          color: 'white',
          fontSize: 48,
          fontWeight: '600',
        }}
      >
        {safeTemp}
      </Text>

      <Text
        style={{
          color: '#BBBBBB',
          fontSize: 18,
          marginTop: 4,
        }}
      >
        Celsius
      </Text>
    </View>
  );
}
