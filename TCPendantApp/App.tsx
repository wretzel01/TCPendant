import React from 'react';
import { BLEProvider } from './src/BLEProvider';
import HomeScreen from './src/screens/HomeScreen';

export default function App() {
  return (
    <BLEProvider>
      <HomeScreen />
    </BLEProvider>
  );
}
