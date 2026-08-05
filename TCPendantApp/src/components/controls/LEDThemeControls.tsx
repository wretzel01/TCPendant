import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface Props {
  device: any;
  setLEDTheme: (device: any, themeId: number) => void;
}

interface ThemeOption {
  id: number;
  label: string;
  colors: [string, string];
}

const THEMES: ThemeOption[] = [
  { id: 0, label: 'Amber', colors: ['#FF9500', '#FF5E00'] },
  { id: 1, label: 'Fire', colors: ['#FF3B30', '#FF9500'] },
  { id: 2, label: 'Ice', colors: ['#007AFF', '#5AC8FA'] },
  { id: 3, label: 'Magic', colors: ['#AF52DE', '#5856D6'] },
  { id: 4, label: 'Christmas', colors: ['#34C759', '#FF3B30'] },
  { id: 5, label: 'Halloween', colors: ['#FF9500', '#AF52DE'] },
  { id: 6, label: 'Valentine', colors: ['#FF2D55', '#FF375F'] },
  { id: 7, label: 'Soft White', colors: ['#E5E5EA', '#FFD60A'] },
  { id: 8, label: 'Rainbow', colors: ['#FF3B30', '#007AFF'] },
];

export default function LEDThemeControls({ device, setLEDTheme }: Props) {
  const [selectedThemeId, setSelectedThemeId] = useState<number>(0);

  const handleSelect = (themeId: number) => {
    setSelectedThemeId(themeId);
    setLEDTheme(device, themeId);
  };

  return (
    <View style={styles.container}>
      {THEMES.map((t) => {
        const isSelected = selectedThemeId === t.id;

        return (
          <TouchableOpacity
            key={t.id}
            activeOpacity={0.8}
            onPress={() => handleSelect(t.id)}
            style={[
              styles.themePill,
              isSelected && styles.selectedPill,
            ]}
          >
            <View style={styles.previewContainer}>
              <View style={[styles.colorDot, { backgroundColor: t.colors[0] }]} />
              <View style={[styles.colorDot, { backgroundColor: t.colors[1], marginLeft: -5 }]} />
            </View>

            <Text style={[styles.label, isSelected && styles.selectedLabel]}>
              {t.label}
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
    gap: 10,
    justifyContent: 'center',
    paddingVertical: 4,
  },
  themePill: {
    flexDirection: 'row',
    alignItems: 'center',
    paddingVertical: 10,
    paddingHorizontal: 14,
    borderRadius: 20,
    backgroundColor: 'rgba(0, 0, 0, 0.25)',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.08)',
  },
  selectedPill: {
    borderColor: '#FFFFFF',
    backgroundColor: 'rgba(255, 255, 255, 0.12)',
  },
  previewContainer: {
    flexDirection: 'row',
    alignItems: 'center',
    marginRight: 8,
  },
  colorDot: {
    width: 12,
    height: 12,
    borderRadius: 6,
    borderWidth: 1,
    borderColor: 'rgba(0, 0, 0, 0.4)',
  },
  label: {
    color: '#8E8E93',
    fontSize: 13,
    fontWeight: '600',
  },
  selectedLabel: {
    color: '#FFFFFF',
  },
});