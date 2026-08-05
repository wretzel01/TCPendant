import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

interface ColorOption {
  label: string;
  rgb: [number, number, number];
  hex: string;
}

const COLORS: ColorOption[] = [
  { label: 'Red', rgb: [255, 0, 0], hex: '#FF0000' },
  { label: 'Orange', rgb: [255, 80, 0], hex: '#FF5000' },
  { label: 'Yellow', rgb: [255, 180, 0], hex: '#FFB400' },
  { label: 'Warm White', rgb: [255, 200, 120], hex: '#FFC878' },
  { label: 'Green', rgb: [0, 255, 0], hex: '#00FF00' },
  { label: 'Cyan', rgb: [0, 255, 255], hex: '#00FFFF' },
  { label: 'Blue', rgb: [0, 0, 255], hex: '#0000FF' },
  { label: 'Purple', rgb: [180, 0, 255], hex: '#B400FF' },
  { label: 'Pink', rgb: [255, 0, 150], hex: '#FF0096' },
  { label: 'Cool White', rgb: [200, 255, 255], hex: '#C8FFFF' },
];

interface Props {
  device: any;
  setLEDColor: (device: any, r: number, g: number, b: number) => void;
}

export default function LEDColorControls({ device, setLEDColor }: Props) {
  const [selectedHex, setSelectedHex] = useState<string>('#FF5000');

  const handleSelect = (color: ColorOption) => {
    setSelectedHex(color.hex);
    setLEDColor(device, ...color.rgb);
  };

  return (
    <View style={styles.container}>
      <View style={styles.grid}>
        {COLORS.map((c) => {
          const isSelected = selectedHex === c.hex;
          return (
            <TouchableOpacity
              key={c.label}
              activeOpacity={0.8}
              onPress={() => handleSelect(c)}
              style={[
                styles.swatch,
                { backgroundColor: c.hex },
                isSelected && styles.selectedSwatch,
              ]}
            >
              {isSelected && <View style={styles.innerDot} />}
            </TouchableOpacity>
          );
        })}
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    paddingVertical: 8,
  },
  grid: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'center',
    gap: 12,
  },
  swatch: {
    width: 44,
    height: 44,
    borderRadius: 22,
    justifyContent: 'center',
    alignItems: 'center',
    borderWidth: 2,
    borderColor: 'transparent',
  },
  selectedSwatch: {
    borderColor: '#FFFFFF',
    transform: [{ scale: 1.1 }],
  },
  innerDot: {
    width: 8,
    height: 8,
    borderRadius: 4,
    backgroundColor: '#FFFFFF',
  },
});