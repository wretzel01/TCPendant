import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDThemeControls({ device, setLEDTheme }) {
  const themes = [
    { id: 0, label: "Amber" },
    { id: 1, label: "Fire" },
    { id: 2, label: "Ice" },
    { id: 3, label: "Magic" },
    { id: 4, label: "Christmas" },
    { id: 5, label: "Halloween" },
    { id: 6, label: "Valentine" },
    { id: 7, label: "Soft White" },
    { id: 8, label: "Rainbow" },
  ];

  return (
    <View style={{ flexDirection: 'row', flexWrap: 'wrap', justifyContent: 'center' }}>
      {themes.map(t => (
        <ControlButton
          key={t.id}
          label={t.label}
          onPress={() => setLEDTheme(device, t.id)}
        />
      ))}
    </View>
  );
}
