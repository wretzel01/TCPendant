import React, { useRef, useEffect, useState } from 'react';
import { View, Text, Animated, PanResponder, Pressable } from 'react-native';

export default function TempWheel({ value, onChange }) {
  const MIN = 35;
  const MAX = 50;

  const temps = [];
  for (let t = MIN; t <= MAX; t++) temps.push(t);

  // Local state for selected temp (safe, stable)
  const [selected, setSelected] = useState(value);

  // Animated scroll position (in index units)
  const scroll = useRef(new Animated.Value(value - MIN)).current;

  // Debounce timer
  const commitTimer = useRef(null);

  // Convert scroll → nearest temp
  const tempForScroll = (s) => {
    const clamped = Math.max(0, Math.min(temps.length - 1, s));
    return MIN + Math.round(clamped);
  };

  // Commit BLE update only after stable
  const commitTemp = (t) => {
    clearTimeout(commitTimer.current);
    commitTimer.current = setTimeout(() => {
      onChange(t); // BLE write ONCE
    }, 250);
  };

  // Gesture handler
  const pan = useRef(
    PanResponder.create({
      onStartShouldSetPanResponder: () => true,
      onPanResponderMove: (_, gesture) => {
        const delta = gesture.dy * 0.05; // smoothing
        const newScroll = selected - MIN + delta;

        Animated.timing(scroll, {
          toValue: newScroll,
          duration: 0,
          useNativeDriver: false,
        }).start();

        const newTemp = tempForScroll(newScroll);
        setSelected(newTemp);
        commitTemp(newTemp);
      },
      onPanResponderRelease: () => {
        Animated.spring(scroll, {
          toValue: selected - MIN,
          useNativeDriver: false,
          speed: 10,
          bounciness: 6,
        }).start();
      },
    })
  ).current;

  // Sync external value → internal state
  useEffect(() => {
    setSelected(value);
    Animated.spring(scroll, {
      toValue: value - MIN,
      useNativeDriver: false,
      speed: 10,
      bounciness: 6,
    }).start();
  }, [value]);

  return (
    <View
      style={{
        width: 120,
        height: 150,
        overflow: 'hidden',
        alignItems: 'center',
      }}
      {...pan.panHandlers}
    >
      {temps.map((t, i) => {
        const isSelected = t === selected;

        return (
          <Pressable
            key={t}
            onPress={() => {
              setSelected(t);
              commitTemp(t);

              Animated.spring(scroll, {
                toValue: t - MIN,
                useNativeDriver: false,
                speed: 10,
                bounciness: 6,
              }).start();
            }}
            style={{
              height: 50,
              justifyContent: 'center',
              alignItems: 'center',
            }}
          >
            <Animated.Text
              style={{
                fontSize: isSelected ? 32 : 22,
                color: isSelected ? 'white' : '#777',
                fontWeight: isSelected ? '700' : '400',
                transform: [
                  {
                    translateY: scroll.interpolate({
                      inputRange: [i - 1, i, i + 1],
                      outputRange: [-50, 0, 50],
                      extrapolate: 'clamp',
                    }),
                  },
                ],
              }}
            >
              {t}
            </Animated.Text>
          </Pressable>
        );
      })}
    </View>
  );
}
