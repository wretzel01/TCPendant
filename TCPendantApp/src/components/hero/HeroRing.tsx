import React from 'react';
import { View } from 'react-native';

export default function HeroRing({ size }) {
  const ringSize = size * 0.70;

  return (
    <View
      style={{
        position: 'absolute',
        width: ringSize,
        height: ringSize,
        borderRadius: ringSize / 2,
        borderWidth: 8,
        borderColor: 'white',

        // ⭐ Center it
        left: (size - ringSize) / 2,
        top: (size - ringSize) / 2,
      }}
    />
  );
}
