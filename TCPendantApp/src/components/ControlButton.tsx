import React from 'react';
import { Pressable, Text, View } from 'react-native';

export default function ControlButton({ label, onPress }) {
  return (
    <Pressable
      onPress={onPress}
      style={{
        backgroundColor: '#333',
        paddingVertical: 12,
        paddingHorizontal: 20,
        borderRadius: 8,
        marginHorizontal: 10,
        borderWidth: 1,
        borderColor: '#555',
      }}
    >
      <Text style={{ color: 'white', fontSize: 18 }}>{label}</Text>
    </Pressable>
  );
}
