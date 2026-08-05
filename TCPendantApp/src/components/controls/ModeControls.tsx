import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface Props {
  device: any;
  setMode: (device: any, mode: number) => void;
}

interface ModeOption {
  id: number;
  label: string;
  sublabel: string;
  activeColor: string;
}

const MODES: ModeOption[] = [
  { id: 0, label: 'Off', sublabel: 'Standby', activeColor: '#8E8E93' },
  { id: 1, label: 'Normal', sublabel: 'Eco Warm', activeColor: '#FF9500' },
  { id: 2, label: 'High', sublabel: 'Max Thermal', activeColor: '#FF3B30' },
];

export default function ModeControls({ device, setMode }: Props) {
  const [activeMode, setActiveMode] = useState<number>(1); // Default to Normal (1)

  const handleModeChange = (modeId: number) => {
    setActiveMode(modeId);
    setMode(device, modeId);
  };

  return (
    <View style={styles.container}>
      {MODES.map((mode) => {
        const isActive = activeMode === mode.id;

        return (
          <TouchableOpacity
            key={mode.id}
            activeOpacity={0.8}
            onPress={() => handleModeChange(mode.id)}
            style={[
              styles.modeCard,
              isActive && {
                borderColor: mode.activeColor,
                backgroundColor: 'rgba(255, 255, 255, 0.08)',
              },
            ]}
          >
            <View
              style={[
                styles.indicatorDot,
                { backgroundColor: isActive ? mode.activeColor : 'rgba(255, 255, 255, 0.2)' },
              ]}
            />
            <Text style={[styles.modeLabel, isActive && styles.activeText]}>
              {mode.label}
            </Text>
            <Text style={styles.modeSublabel}>{mode.sublabel}</Text>
          </TouchableOpacity>
        );
      })}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    gap: 10,
    justifyContent: 'space-between',
    paddingVertical: 4,
  },
  modeCard: {
    flex: 1,
    alignItems: 'center',
    paddingVertical: 14,
    paddingHorizontal: 8,
    borderRadius: 14,
    backgroundColor: 'rgba(0, 0, 0, 0.25)',
    borderWidth: 1.5,
    borderColor: 'rgba(255, 255, 255, 0.06)',
  },
  indicatorDot: {
    width: 8,
    height: 8,
    borderRadius: 4,
    marginBottom: 8,
  },
  modeLabel: {
    color: '#8E8E93',
    fontSize: 15,
    fontWeight: '700',
    marginBottom: 2,
  },
  activeText: {
    color: '#FFFFFF',
  },
  modeSublabel: {
    color: 'rgba(255, 255, 255, 0.4)',
    fontSize: 11,
    fontWeight: '500',
  },
});