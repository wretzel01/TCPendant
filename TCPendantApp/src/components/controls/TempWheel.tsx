import React, { useState, useRef } from 'react';
import { View, Text, Pressable, Animated, Image } from 'react-native';
import { getTempColor } from './TempColor';
import glowdotImg from '../../assets/glowdot.png';

const glowSize = 240;

export default function TempWheel({ device, onChange }) {
  const [temp, setTemp] = useState(40);

  const scale = useRef(new Animated.Value(1)).current;

  const bump = () => {
    Animated.sequence([
      Animated.timing(scale, {
        toValue: 1.08,
        duration: 100,
        useNativeDriver: true,
      }),
      Animated.timing(scale, {
        toValue: 1.0,
        duration: 100,
        useNativeDriver: true,
      }),
    ]).start();
  };

  const changeTemp = (delta: number) => {
    const next = Math.min(45, Math.max(35, temp + delta));
    setTemp(next);
    bump();
    onChange(device, next);
  };

  const tint = getTempColor(temp);

  return (
    <View
      style={{
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'center',
        gap: 30,
        paddingVertical: 20,
      }}
    >
      {/* MINUS BUTTON + BLUE GLOWDOT */}
      <View
        style={{
          position: 'relative',
          width: 60,
          height: 60,
          justifyContent: 'center',
          alignItems: 'center',
        }}
      >
        <Image
          source={glowdotImg}
          style={{
            position: 'absolute',
            width: glowSize,
            height: glowSize,
            tintColor: 'rgb(42, 72, 171)',
            opacity: 0.55,

            // ⭐ Center the glowdot behind the button
            left: '50%',
            top: '50%',
            transform: [
              { translateX: -glowSize / 2 },
              { translateY: -glowSize / 2 },
            ],
          }}
        />
        <Pressable
          onPress={() => changeTemp(-1)}
          style={({ pressed }) => ({
            width: 60,
            height: 60,
            borderRadius: 30,
            justifyContent: 'center',
            alignItems: 'center',
            backgroundColor: pressed ? '#333' : '#222',
          })}
        >
          <Text style={{ color: 'white', fontSize: 28 }}>−</Text>
        </Pressable>
      </View>

      {/* TEMPERATURE DISPLAY */}
      <Animated.View
        style={{
          transform: [{ scale }],
          paddingHorizontal: 28,
          paddingVertical: 12,
          backgroundColor: '#1a1a1a',
          borderRadius: 14,
          borderWidth: 2,
          borderColor: tint,
          shadowColor: tint,
          shadowOpacity: 0.25,
          shadowRadius: 8,
          shadowOffset: { width: 0, height: 0 },
        }}
      >
        <Text
          style={{
            color: 'white',
            fontSize: 34,
            fontWeight: '700',
          }}
        >
          {temp}°C
        </Text>
      </Animated.View>

      {/* PLUS BUTTON + RED GLOWDOT */}
      <View
        style={{
          position: 'relative',
          width: 60,
          height: 60,
          justifyContent: 'center',
          alignItems: 'center',
        }}
      >
        <Image
          source={glowdotImg}
          style={{
            position: 'absolute',
            width: glowSize,
            height: glowSize,
            tintColor: 'rgb(182, 36, 56)',
            opacity: 0.55,

            // ⭐ Center the glowdot behind the button
            left: '50%',
            top: '50%',
            transform: [
              { translateX: -glowSize / 2 },
              { translateY: -glowSize / 2 },
            ],
          }}
        />
        <Pressable
          onPress={() => changeTemp(1)}
          style={({ pressed }) => ({
            width: 60,
            height: 60,
            borderRadius: 30,
            justifyContent: 'center',
            alignItems: 'center',
            backgroundColor: pressed ? '#333' : '#222',
          })}
        >
          <Text style={{ color: 'white', fontSize: 28 }}>+</Text>
        </Pressable>
      </View>
    </View>
  );
}
