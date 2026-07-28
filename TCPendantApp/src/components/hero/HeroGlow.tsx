import React, { useEffect, useRef } from 'react';
import { Animated } from 'react-native';
import { Easing } from 'react-native';

import glowringImg from '../../assets/glowring.png';

// Temperature → color stops
const TEMP_COLORS = [
  { t: 15, color: 'rgb(0, 40, 120)' },
  { t: 20, color: 'rgb(0, 120, 255)' },
  { t: 25, color: 'rgb(120, 200, 255)' },
  { t: 30, color: 'rgb(255, 255, 120)' },
  { t: 35, color: 'rgb(255, 165, 0)' },
  { t: 40, color: 'rgb(255, 60, 60)' },
];

function interpolateColor(c1, c2, t) {
  const [r1, g1, b1] = c1.match(/\d+/g).map(Number);
  const [r2, g2, b2] = c2.match(/\d+/g).map(Number);
  return `rgb(${r1 + (r2 - r1) * t}, ${g1 + (g2 - g1) * t}, ${b1 + (b2 - b1) * t})`;
}

function getTempColor(temp) {
  if (temp == null) return 'rgb(0,0,0)';
  for (let i = 0; i < TEMP_COLORS.length - 1; i++) {
    const a = TEMP_COLORS[i];
    const b = TEMP_COLORS[i + 1];
    if (temp >= a.t && temp <= b.t) {
      const t = (temp - a.t) / (b.t - a.t);
      return interpolateColor(a.color, b.color, t);
    }
  }
  return TEMP_COLORS[TEMP_COLORS.length - 1].color;
}

export default function HeroGlow({ temp, pwm, size }) {
  const rawProgress = Math.min(Math.max(pwm / 255, 0), 1);

  const glowProgress = useRef(new Animated.Value(rawProgress)).current;

  useEffect(() => {
    Animated.timing(glowProgress, {
      toValue: rawProgress,
      duration: 600,
      easing: Easing.out(Easing.cubic),
      useNativeDriver: false,
    }).start();
  }, [rawProgress]);

  // ⭐ Only scale changes with PWM
  const scale = glowProgress.interpolate({
    inputRange: [0, 1],
    outputRange: [1.02, 1.2],
  });

  const tintColor = getTempColor(temp);

  return (
    <Animated.Image
      source={glowringImg}
      style={{
        position: 'absolute',
        width: size,
        height: size,
        transform: [{ scale }],
        tintColor: tintColor,
        resizeMode: 'contain',
      }}
    />
  );
}
