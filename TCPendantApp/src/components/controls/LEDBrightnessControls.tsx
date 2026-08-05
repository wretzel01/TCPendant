import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface Props {
  device: any;
  setLEDBrightness: (device: any, val: number) => void;
}

interface BrightnessLevel {
  label: string;
  value: number;
  bars: number;
}

const LEVELS: BrightnessLevel[] = [
  { label: 'Low', value: 40, bars: 1 },
  { label: 'Med', value: 120, bars: 2 },
  { label: 'High', value: 255, bars: 3 },
];

export default function LEDBrightnessControls({ device, setLEDBrightness }: Props) {
  const [selectedVal, setSelectedVal] = useState<number>(120);

  const handleSelect = (val: number) => {
    setSelectedVal(val);
    setLEDBrightness(device, val);
  };

  return (
    <View style={styles.container}>
      {LEVELS.map((level) => {
        const isSelected = selectedVal === level.value;

        return (
          <TouchableOpacity
            key={level.label}
            activeOpacity={0.8}
            onPress={() => handleSelect(level.value)}
            style={[
              styles.card,
              isSelected && styles.selectedCard,
            ]}
          >
            {/* Visual Brightness Indicator Bars */}
            <View style={styles.barContainer}>
              {[1, 2, 3].map((barIndex) => (
                <View
                  key={barIndex}
                  style={[
                    styles.bar,
                    { height: 6 + barIndex * 4 },
                    barIndex <= level.bars
                      ? { backgroundColor: isSelected ? '#FFFFFF' : 'rgba(255, 255, 255, 0.4)' }
                      : { backgroundColor: 'rgba(255, 255, 255, 0.1)' },
                  ]}
                />
              ))}
            </View>

            <Text style={[styles.label, isSelected && styles.selectedLabel]}>
              {level.label}
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
    gap: 10,
    justifyContent: 'space-between',
    paddingVertical: 4,
  },
  card: {
    flex: 1,
    alignItems: 'center',
    paddingVertical: 12,
    borderRadius: 14,
    backgroundColor: 'rgba(0, 0, 0, 0.25)',
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.08)',
  },
  selectedCard: {
    borderColor: '#FFFFFF',
    backgroundColor: 'rgba(255, 255, 255, 0.12)',
  },
  barContainer: {
    flexDirection: 'row',
    alignItems: 'flex-end',
    gap: 3,
    height: 18,
    marginBottom: 6,
  },
  bar: {
    width: 4,
    borderRadius: 2,
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