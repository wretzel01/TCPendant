import React from 'react';
import { View } from 'react-native';
import HeroGlow from './HeroGlow';
import HeroRing from './HeroRing';
import HeroTemp from './HeroTemp';
import HeroPWM from './HeroPWM';   // ⭐ NEW

export default function HeroGauge({ temp, pwm }) {
  const SIZE = 260;

  return (
    <View
      style={{
        width: SIZE,
        height: SIZE,
        justifyContent: 'center',
        alignItems: 'center',
        position: 'relative',
      }}
    >
      <HeroGlow temp={temp} pwm={pwm} size={SIZE} />
      <HeroRing size={SIZE} />
      <HeroTemp temp={temp} />

      {/* ⭐ PWM overlay */}
      <HeroPWM pwm={pwm} />
    </View>
  );
}
