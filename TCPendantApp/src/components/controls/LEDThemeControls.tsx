import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface Props {
  device: any;
  setLEDTheme: (device: any, themeId: number) => void;
}

interface ThemeOption {
  id: number;
  label: string;
  emoji: string;
}

const THEMES: ThemeOption[] = [
  { id: 1, label: 'Amber', emoji: '🟠' },
  { id: 2, label: 'Fire', emoji: '🔥' },
  { id: 3, label: 'Ice', emoji: '❄️' },
  { id: 4, label: 'Magic', emoji: '✨' },
  { id: 5, label: 'Christmas', emoji: '🎄' },
  { id: 6, label: 'Halloween', emoji: '🎃' },
  { id: 7, label: 'Valentine', emoji: '💖' },
  { id: 8, label: 'Soft White', emoji: '⚪' },
  { id: 9, label: 'Rainbow', emoji: '🌈' },
];

export default function LEDThemeControls({ device, setLEDTheme }: Props) {
  const [selectedId, setSelectedId] = useState<number>(1);

  const handleSelect = (id: number) => {
    setSelectedId(id);
    setLEDTheme(device, id);
  };

  return (
    <View style={styles.container}>
      {THEMES.map((theme) => {
        const isSelected = selectedId === theme.id;

        return (
          <TouchableOpacity
            key={theme.id}
            activeOpacity={0.8}
            onPress={() => handleSelect(theme.id)}
            style={[
              styles.chip,
              isSelected && styles.selectedChip,
            ]}
          >
            <Text style={styles.emoji}>{theme.emoji}</Text>
            <Text style={[styles.label, isSelected && styles.selectedText]}>
              {theme.label}
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
  emoji: {
    fontSize: 14,
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