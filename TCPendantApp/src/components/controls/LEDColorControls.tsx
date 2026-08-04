import React from 'react';
import { View } from 'react-native';
import ControlButton from '../common/ControlButton';

export default function LEDColorControls({ device, setLEDColor }) {
  const colors = [
    { label: "Red",       rgb: [255,   0,   0] },
    { label: "Orange",    rgb: [255,  80,   0] },
    { label: "Yellow",    rgb: [255, 180,   0] },
    { label: "Lime",      rgb: [180, 255,   0] },
    { label: "Green",     rgb: [  0, 255,   0] },
    { label: "Cyan",      rgb: [  0, 255, 255] },
    { label: "Blue",      rgb: [  0,   0, 255] },
    { label: "Purple",    rgb: [180,   0, 255] },
    { label: "Pink",      rgb: [255,   0, 150] },
    { label: "Magenta",   rgb: [255,   0, 255] },
    { label: "White",     rgb: [255, 255, 255] },
    { label: "WarmWhite", rgb: [255, 200, 120] },
    { label: "CoolWhite", rgb: [200, 255, 255] },
  ];

  return (
    <View style={{ flexDirection: 'row', flexWrap: 'wrap', justifyContent: 'center' }}>
      {colors.map(c => (
        <ControlButton
          key={c.label}
          label={c.label}
          onPress={() => setLEDColor(device, ...c.rgb)}
        />
      ))}
    </View>
  );
}
