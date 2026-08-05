import React, { useEffect, useRef } from 'react';
import { View, Text, Animated, Pressable, StyleSheet } from 'react-native';

interface Props {
  connected: boolean;
  found?: boolean;
  onRetry?: () => void;
}

export default function ConnectionBanner({ connected, found, onRetry }: Props) {
  const pulseAnim = useRef(new Animated.Value(1)).current;
  const opacityAnim = useRef(new Animated.Value(0.4)).current;

  useEffect(() => {
    if (!connected) {
      const animation = Animated.loop(
        Animated.parallel([
          Animated.sequence([
            Animated.timing(pulseAnim, {
              toValue: 1.25,
              duration: 1200,
              useNativeDriver: true,
            }),
            Animated.timing(pulseAnim, {
              toValue: 1.0,
              duration: 1200,
              useNativeDriver: true,
            }),
          ]),
          Animated.sequence([
            Animated.timing(opacityAnim, {
              toValue: 0.8,
              duration: 1200,
              useNativeDriver: true,
            }),
            Animated.timing(opacityAnim, {
              toValue: 0.3,
              duration: 1200,
              useNativeDriver: true,
            }),
          ]),
        ])
      );
      animation.start();
      return () => animation.stop();
    }
  }, [connected]);

  // If connected, render the compact top status badge
  if (connected) {
    return (
      <View style={styles.compactContainer}>
        <View style={styles.statusRow}>
          <View style={[styles.statusDot, { backgroundColor: '#34C759' }]} />
          <Text style={styles.compactText}>TCPendant Connected</Text>
        </View>
      </View>
    );
  }

  // If disconnected, render a full hero state to fill the screen nicely
  return (
    <View style={styles.disconnectedHero}>
      {/* Animated Radar Pulse Ring */}
      <View style={styles.radarWrapper}>
        <Animated.View
          style={[
            styles.pulseRing,
            {
              transform: [{ scale: pulseAnim }],
              opacity: opacityAnim,
              borderColor: found ? '#FF9500' : '#FF5E3A',
            },
          ]}
        />
        <View
          style={[
            styles.centerIconCircle,
            { backgroundColor: found ? 'rgba(255, 149, 0, 0.15)' : 'rgba(255, 94, 58, 0.15)' },
          ]}
        >
          <Text style={styles.bluetoothIcon}>📡</Text>
        </View>
      </View>

      <Text style={styles.heroTitle}>
        {found ? 'Pendant Detected' : 'No Pendant Connected'}
      </Text>
      
      <Text style={styles.heroSubtext}>
        {found
          ? 'Establishing Bluetooth link…'
          : 'Make sure your TCPendant is powered on and within range.'}
      </Text>

      {onRetry && (
        <Pressable
          onPress={onRetry}
          style={({ pressed }) => [
            styles.connectBtn,
            pressed && styles.connectBtnPressed,
          ]}
        >
          <Text style={styles.connectBtnText}>
            {found ? 'Connecting…' : 'Scan for Device'}
          </Text>
        </Pressable>
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  /* Connected Compact Badge */
  compactContainer: {
    alignSelf: 'flex-start',
    paddingVertical: 6,
    paddingHorizontal: 12,
    borderRadius: 16,
    backgroundColor: 'rgba(255, 255, 255, 0.06)',
    borderWidth: 1,
    borderColor: 'rgba(52, 199, 89, 0.25)',
    marginBottom: 12,
  },
  statusRow: {
    flexDirection: 'row',
    alignItems: 'center',
    gap: 8,
  },
  statusDot: {
    width: 7,
    height: 7,
    borderRadius: 3.5,
  },
  compactText: {
    color: '#FFFFFF',
    fontSize: 12,
    fontWeight: '600',
  },

  /* Disconnected Hero Screen */
  disconnectedHero: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 48,
    paddingHorizontal: 24,
    marginVertical: 20,
    borderRadius: 24,
    backgroundColor: 'rgba(255, 255, 255, 0.03)',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.06)',
  },
  radarWrapper: {
    width: 100,
    height: 100,
    alignItems: 'center',
    justifyContent: 'center',
    marginBottom: 24,
  },
  pulseRing: {
    position: 'absolute',
    width: 90,
    height: 90,
    borderRadius: 45,
    borderWidth: 2,
  },
  centerIconCircle: {
    width: 64,
    height: 64,
    borderRadius: 32,
    alignItems: 'center',
    justifyContent: 'center',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.1)',
  },
  bluetoothIcon: {
    fontSize: 26,
  },
  heroTitle: {
    color: '#FFFFFF',
    fontSize: 20,
    fontWeight: '700',
    marginBottom: 8,
    textAlign: 'center',
  },
  heroSubtext: {
    color: '#8E8E93',
    fontSize: 14,
    textAlign: 'center',
    lineHeight: 20,
    marginBottom: 24,
    paddingHorizontal: 10,
  },
  connectBtn: {
    backgroundColor: 'rgba(255, 255, 255, 0.12)',
    paddingHorizontal: 24,
    paddingVertical: 12,
    borderRadius: 20,
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.18)',
  },
  connectBtnPressed: {
    backgroundColor: 'rgba(255, 255, 255, 0.22)',
  },
  connectBtnText: {
    color: '#FFFFFF',
    fontSize: 14,
    fontWeight: '600',
  },
});