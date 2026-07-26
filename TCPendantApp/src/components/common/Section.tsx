import React from 'react';
import { View, Text } from 'react-native';

export default function Section({ title, children }) {
  return (
    <View style={{ marginTop: 30, alignItems: 'center' }}>
      <Text style={{ color: 'white', fontSize: 20, marginBottom: 10 }}>
        {title}
      </Text>
      {children}
    </View>
  );
}
