import React from 'react';
import { StyleSheet, View, StatusBar } from 'react-native';
import { SafeAreaView } from 'react-native-safe-area-context';
import LinearGradient from 'react-native-linear-gradient';

interface ScreenContainerProps {
  children: React.ReactNode;
}

export default function ScreenContainer({ children }: ScreenContainerProps) {
  return (
    <SafeAreaView style={styles.container} edges={['top', 'left', 'right', 'bottom']}>
      <StatusBar barStyle="light-content" backgroundColor="#0B0D12" translucent={false} />

      {/* STATIC BACKGROUND GRADIENT LAYER */}
      <View style={styles.backdropContainer} pointerEvents="none">
        {/* Top Warm Thermal Accent */}
        <LinearGradient
          colors={['rgba(255, 94, 58, 0.16)', 'rgba(255, 42, 85, 0.04)', 'transparent']}
          style={styles.topGradient}
          start={{ x: 0.5, y: 0 }}
          end={{ x: 0.5, y: 1 }}
        />

        {/* Bottom Ambient Tint */}
        <LinearGradient
          colors={['transparent', 'rgba(90, 200, 250, 0.03)']}
          style={styles.bottomGradient}
          start={{ x: 0.5, y: 0 }}
          end={{ x: 0.5, y: 1 }}
        />
      </View>

      {/* MAIN CONTENT WRAPPER */}
      <View style={styles.content}>
        {children}
      </View>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#0B0D12', // Base OLED dark color guarantees background during transitions
  },
  backdropContainer: {
    ...StyleSheet.absoluteFillObject,
    zIndex: 0,
  },
  topGradient: {
    position: 'absolute',
    top: 0,
    left: 0,
    right: 0,
    height: 320,
  },
  bottomGradient: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    right: 0,
    height: 220,
  },
  content: {
    flex: 1,
    paddingHorizontal: 16,
    paddingTop: 8,
    zIndex: 1,
  },
});