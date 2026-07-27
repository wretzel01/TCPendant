import React from 'react';
import { View } from 'react-native';
import HeroGlow from './HeroGlow';
import HeroRing from './HeroRing';
import HeroTemp from './HeroTemp';

export default function HeroGauge({ temp, pwm }) {
  const SIZE = 260;

  return (
    <View
      style={{
        width: SIZE,
        height: SIZE,

        // ⭐ This centers ALL children perfectly
        justifyContent: 'center',
        alignItems: 'center',

        // ⭐ No absolute positioning here
        position: 'relative',
      }}
    >
      <HeroGlow temp={temp} pwm={pwm} size={SIZE} />
      <HeroRing size={SIZE} />
      <HeroTemp temp={temp} />
    </View>
  );
}
