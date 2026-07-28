import React, { useEffect, useRef } from 'react';
import { View, Text, Animated, Pressable } from 'react-native';

export default function ConnectionBanner({ connected, found, onRetry }) {
  const pulse = useRef(new Animated.Value(1)).current;

  useEffect(() => {
    if (!connected) {
      Animated.loop(
        Animated.sequence([
          Animated.timing(pulse, {
            toValue: 1.05,
            duration: 600,
            useNativeDriver: true,
          }),
          Animated.timing(pulse, {
            toValue: 1.0,
            duration: 600,
            useNativeDriver: true,
          }),
        ])
      ).start();
    }
  }, [connected]);

  const bg = connected
    ? 'rgba(30, 143, 77, 0.9)'   // green
    : found
      ? 'rgba(255, 165, 0, 0.9)' // orange (found but not connected)
      : 'rgba(143, 30, 30, 0.9)'; // red (searching)

  const text = connected
    ? 'Connected to TCPendant'
    : found
      ? 'Device Found — Connecting…'
      : 'Searching for TCPendant…';

  return (
    <Animated.View
      style={{
        transform: [{ scale: connected ? 1 : pulse }],
        backgroundColor: bg,
        padding: 14,
        borderRadius: 10,
        marginBottom: 24,
        alignItems: 'center',
        justifyContent: 'center',
        shadowColor: bg,
        shadowOpacity: 0.4,
        shadowRadius: 10,
        shadowOffset: { width: 0, height: 0 },
      }}
    >
      <Text style={{ color: 'white', fontSize: 18, fontWeight: '600' }}>
        {text}
      </Text>

      {!connected && onRetry && (
        <Pressable
          onPress={onRetry}
          style={{
            marginTop: 8,
            paddingHorizontal: 12,
            paddingVertical: 6,
            backgroundColor: 'rgba(255,255,255,0.15)',
            borderRadius: 6,
          }}
        >
          <Text style={{ color: 'white', fontSize: 14 }}>Retry</Text>
        </Pressable>
      )}
    </Animated.View>
  );
}
