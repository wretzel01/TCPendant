import React, { useState, useRef } from 'react';
import { View, Text, Pressable, Animated, Image, StyleSheet } from 'react-native';
import { getTempColor } from './TempColor';
import glowdotImg from '../../assets/glowdot.png';

const GLOW_SIZE = 160;
const MIN_TEMP = 35;
const MAX_TEMP = 45;

interface Props {
  device: any;
  onChange: (device: any, temp: number) => void;
}

export default function TempWheel({ device, onChange }: Props) {
  const [temp, setTemp] = useState<number>(40);

  const displayScale = useRef(new Animated.Value(1)).current;
  const minusScale = useRef(new Animated.Value(1)).current;
  const plusScale = useRef(new Animated.Value(1)).current;

  const bumpDisplay = () => {
    Animated.sequence([
      Animated.timing(displayScale, {
        toValue: 1.08,
        duration: 90,
        useNativeDriver: true,
      }),
      Animated.timing(displayScale, {
        toValue: 1.0,
        duration: 90,
        useNativeDriver: true,
      }),
    ]).start();
  };

  const animateButtonPress = (animVar: Animated.Value) => {
    Animated.sequence([
      Animated.timing(animVar, {
        toValue: 0.9,
        duration: 60,
        useNativeDriver: true,
      }),
      Animated.timing(animVar, {
        toValue: 1.0,
        duration: 60,
        useNativeDriver: true,
      }),
    ]).start();
  };

  const changeTemp = (delta: number) => {
    const next = Math.min(MAX_TEMP, Math.max(MIN_TEMP, temp + delta));
    if (next === temp) return; // At min/max limits

    if (delta < 0) animateButtonPress(minusScale);
    else animateButtonPress(plusScale);

    setTemp(next);
    bumpDisplay();
    onChange(device, next);
  };

  const tint = getTempColor(temp);
  const isAtMin = temp <= MIN_TEMP;
  const isAtMax = temp >= MAX_TEMP;

  return (
    <View style={styles.container}>
      {/* MINUS BUTTON */}
      <Animated.View style={[styles.glowWrapper, { transform: [{ scale: minusScale }] }]}>
        <Image
          source={glowdotImg}
          style={[
            styles.glowDot,
            {
              tintColor: '#2A48AB',
              opacity: isAtMin ? 0.15 : 0.45,
            },
          ]}
        />
        <Pressable
          disabled={isAtMin}
          onPress={() => changeTemp(-1)}
          style={({ pressed }) => [
            styles.btn,
            isAtMin && styles.btnDisabled,
            pressed && styles.btnPressed,
          ]}
        >
          <Text style={[styles.btnText, isAtMin && styles.btnTextDisabled]}>−</Text>
        </Pressable>
      </Animated.View>

      {/* TEMPERATURE DISPLAY CARD */}
      <Animated.View
        style={[
          styles.displayCard,
          {
            borderColor: tint,
            shadowColor: tint,
            transform: [{ scale: displayScale }],
          },
        ]}
      >
        <Text style={styles.tempText}>{temp}°C</Text>
        <Text style={styles.tempSubtext}>Target</Text>
      </Animated.View>

      {/* PLUS BUTTON */}
      <Animated.View style={[styles.glowWrapper, { transform: [{ scale: plusScale }] }]}>
        <Image
          source={glowdotImg}
          style={[
            styles.glowDot,
            {
              tintColor: '#B62438',
              opacity: isAtMax ? 0.15 : 0.45,
            },
          ]}
        />
        <Pressable
          disabled={isAtMax}
          onPress={() => changeTemp(1)}
          style={({ pressed }) => [
            styles.btn,
            isAtMax && styles.btnDisabled,
            pressed && styles.btnPressed,
          ]}
        >
          <Text style={[styles.btnText, isAtMax && styles.btnTextDisabled]}>+</Text>
        </Pressable>
      </Animated.View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'center',
    gap: 20,
    paddingVertical: 12,
  },
  glowWrapper: {
    position: 'relative',
    width: 56,
    height: 56,
    justifyContent: 'center',
    alignItems: 'center',
  },
  glowDot: {
    position: 'absolute',
    width: GLOW_SIZE,
    height: GLOW_SIZE,
    left: '50%',
    top: '50%',
    transform: [
      { translateX: -GLOW_SIZE / 2 },
      { translateY: -GLOW_SIZE / 2 },
    ],
  },
  btn: {
    width: 54,
    height: 54,
    borderRadius: 27,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'rgba(255, 255, 255, 0.08)',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.12)',
  },
  btnPressed: {
    backgroundColor: 'rgba(255, 255, 255, 0.18)',
  },
  btnDisabled: {
    backgroundColor: 'rgba(255, 255, 255, 0.02)',
    borderColor: 'rgba(255, 255, 255, 0.04)',
  },
  btnText: {
    color: '#FFFFFF',
    fontSize: 26,
    fontWeight: '400',
    marginTop: -2,
  },
  btnTextDisabled: {
    color: 'rgba(255, 255, 255, 0.2)',
  },
  displayCard: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingHorizontal: 24,
    paddingVertical: 10,
    backgroundColor: 'rgba(0, 0, 0, 0.35)',
    borderRadius: 16,
    borderWidth: 1.5,
    minWidth: 110,
    shadowOpacity: 0.3,
    shadowRadius: 10,
    shadowOffset: { width: 0, height: 0 },
  },
  tempText: {
    color: '#FFFFFF',
    fontSize: 32,
    fontWeight: '800',
    letterSpacing: 0.5,
  },
  tempSubtext: {
    color: 'rgba(255, 255, 255, 0.4)',
    fontSize: 10,
    fontWeight: '600',
    textTransform: 'uppercase',
    letterSpacing: 1,
    marginTop: -2,
  },
});