import React, { useContext } from 'react';
import { View, Text } from 'react-native';
import { BLEProvider, BLEContext } from './src/BLEProvider';

import ControlButton from './src/components/ControlButton';
import Section from './src/components/Section';
import TelemetryDisplay from './src/components/TelemetryDisplay';

function HomeScreen() {
  const {
    found,
    connected,
    currentTemp,
    currentPWM,
    device,
    setTargetTemp,
    setMode
  } = useContext(BLEContext);

  return (
    <View
      style={{
        flex: 1,
        backgroundColor: 'black',
        justifyContent: 'center',
        alignItems: 'center',
        paddingTop: 40,
      }}
    >
      {/* Connection Status */}
      <Text style={{ color: 'white', fontSize: 24, marginBottom: 20 }}>
        {connected
          ? `Connected to TCPendant`
          : found
            ? `Found TCPendant, connecting...`
            : `Scanning for TCPendant...`}
      </Text>

      {/* Telemetry */}
      {connected && (
        <>
          <TelemetryDisplay temp={currentTemp} pwm={currentPWM} />

          {/* Target Temp Section */}
          <Section title="Set Target Temp">
            <View style={{ flexDirection: 'row' }}>
              <ControlButton
                label="35°C"
                onPress={() => setTargetTemp(device, 35)}
              />
              <ControlButton
                label="40°C"
                onPress={() => setTargetTemp(device, 40)}
              />
            </View>
          </Section>

          {/* Mode Section */}
          <Section title="Set Mode">
            <View style={{ flexDirection: 'row' }}>
              <ControlButton
                label="Off"
                onPress={() => setMode(device, 0)}
              />
              <ControlButton
                label="Heat"
                onPress={() => setMode(device, 1)}
              />
            </View>
          </Section>
        </>
      )}
    </View>
  );
}

export default function App() {
  return (
    <BLEProvider>
      <HomeScreen />
    </BLEProvider>
  );
}
