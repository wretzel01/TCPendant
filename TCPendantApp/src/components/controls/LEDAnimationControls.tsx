import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface Props {
  device: any;
  setLEDAnimation: (device: any, animId: number) => void;
}

interface AnimationOption {
  id: number;
  label: string;
  icon: string;
}

const ANIMATIONS: AnimationOption[] = [
  { id: 1, label: 'Static', icon: '―' },
  { id: 2, label: 'Breathe', icon: '∼' },
  { id: 3, label: 'Pulse', icon: '⚡' },
  { id: 4, label: 'Flicker', icon: '✻' },
  { id: 5, label: 'Twinkle', icon: '✧' },
];

export default function LEDAnimationControls({ device, setLEDAnimation }: Props) {
  const [selectedId, setSelectedId] = useState<number>(1);

  const handleSelect = (id: number) => {
    setSelectedId(id);
    setLEDAnimation(device, id);
  };

  return (
    <View style={styles.container}>
      {ANIMATIONS.map((anim) => {
        const isSelected = selectedId === anim.id;

        return (
          <TouchableOpacity
            key={anim.id}
            activeOpacity={0.8}
            onPress={() => handleSelect(anim.id)}
            style={[
              styles.chip,
              isSelected && styles.selectedChip,
            ]}
          >
            <Text style={[styles.icon, isSelected && styles.selectedText]}>
              {anim.icon}
            </Text>
            <Text style={[styles.label, isSelected && styles.selectedText]}>
              {anim.label}
            </Text>
          </TouchableOpacity>
        );
      })}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    gap: 8,
    justifyContent: 'center',
    paddingVertical: 4,
  },
  chip: {
    flexDirection: 'row',
    alignItems: 'center',
    gap: 6,
    paddingVertical: 10,
    paddingHorizontal: 14,
    borderRadius: 18,
    backgroundColor: 'rgba(0, 0, 0, 0.25)',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.08)',
  },
  selectedChip: {
    borderColor: '#FFFFFF',
    backgroundColor: 'rgba(255, 255, 255, 0.12)',
  },
  icon: {
    color: '#8E8E93',
    fontSize: 14,
    fontWeight: '700',
  },
  label: {
    color: '#8E8E93',
    fontSize: 13,
    fontWeight: '600',
  },
  selectedText: {
    color: '#FFFFFF',
  },
});