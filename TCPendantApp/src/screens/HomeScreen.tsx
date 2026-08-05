import React, { useContext, useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet, ScrollView } from 'react-native';
import { BLEContext } from '../ble/BLEProvider';
import ConnectionBanner from '../components/status/ConnectionBanner';
import HeroGauge from '../components/hero/HeroGauge';
import TempWheel from '../components/controls/TempWheel';
import LEDControlsPanel from '../components/controls/LEDControlsPanel';
import ModeControls from '../components/controls/ModeControls';
import ScreenContainer from '../components/common/ScreenContainer';
import Section from '../components/common/Section';

export default function HomeScreen() {
  const ble = useContext(BLEContext);
  const [activeTab, setActiveTab] = useState<'thermal' | 'led'>('thermal');

  if (!ble) {
    return (
      <ScreenContainer>
        <Text style={styles.initText}>Initializing BLE…</Text>
      </ScreenContainer>
    );
  }

  const {
    connected,
    currentTemp,
    currentPWM,
    batteryPercent,
    batteryVoltage,
    device,
    setTargetTemp,
    setMode,
  } = ble;

  const batteryPctText =
    batteryPercent !== null && batteryPercent !== undefined
      ? `${batteryPercent}%`
      : '—';

  const batteryVoltText =
    batteryVoltage !== null && batteryVoltage !== undefined
      ? `${batteryVoltage.toFixed(2)}V`
      : '';

  return (
    <ScreenContainer>
      <ScrollView contentContainerStyle={styles.scrollContent} showsVerticalScrollIndicator={false}>
        
        {/* TOP STATUS BAR */}
        <View style={styles.statusRow}>
          <ConnectionBanner connected={connected} />
          {connected && (
            <View style={styles.batteryBadge}>
              <Text style={styles.batteryText}>
                ⚡ {batteryPctText} {batteryVoltText ? `(${batteryVoltText})` : ''}
              </Text>
            </View>
          )}
        </View>

        {/* HERO THERMAL DISPLAY */}
        {connected && (
          <View style={styles.heroWrapper}>
            <HeroGauge temp={currentTemp} pwm={currentPWM} />
          </View>
        )}

        {/* CONTROLS ZONE */}
        {connected && (
          <View style={styles.controlsContainer}>
            {/* SEGMENTED TAB SELECTOR */}
            <View style={styles.tabBar}>
              <TouchableOpacity
                activeOpacity={0.8}
                style={[styles.tab, activeTab === 'thermal' && styles.activeTab]}
                onPress={() => setActiveTab('thermal')}
              >
                <Text style={[styles.tabText, activeTab === 'thermal' && styles.activeTabText]}>
                  Thermal
                </Text>
              </TouchableOpacity>

              <TouchableOpacity
                activeOpacity={0.8}
                style={[styles.tab, activeTab === 'led' && styles.activeTab]}
                onPress={() => setActiveTab('led')}
              >
                <Text style={[styles.tabText, activeTab === 'led' && styles.activeTabText]}>
                  Lighting
                </Text>
              </TouchableOpacity>
            </View>

            {/* TAB CONTENT */}
            {activeTab === 'thermal' ? (
              <View style={styles.tabContent}>
                <View style={styles.card}>
                  <Section title="Target Temperature">
                    <TempWheel device={device} onChange={setTargetTemp} />
                  </Section>
                </View>

                <View style={styles.card}>
                  <Section title="Heating Mode">
                    <ModeControls device={device} setMode={setMode} />
                  </Section>
                </View>
              </View>
            ) : (
              <LEDControlsPanel />
            )}
          </View>
        )}
      </ScrollView>
    </ScreenContainer>
  );
}

const styles = StyleSheet.create({
  scrollContent: {
    paddingBottom: 40,
  },
  initText: {
    color: '#8E8E93',
    textAlign: 'center',
    marginTop: 40,
    fontSize: 16,
  },
  statusRow: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    marginBottom: 16,
  },
  batteryBadge: {
    backgroundColor: 'rgba(255, 255, 255, 0.08)',
    paddingHorizontal: 12,
    paddingVertical: 6,
    borderRadius: 20,
  },
  batteryText: {
    color: '#34C759',
    fontSize: 13,
    fontWeight: '600',
  },
  heroWrapper: {
    alignItems: 'center',
    marginVertical: 12,
  },
  controlsContainer: {
    marginTop: 16,
  },
  tabBar: {
    flexDirection: 'row',
    backgroundColor: 'rgba(0, 0, 0, 0.3)',
    borderRadius: 12,
    padding: 4,
    marginBottom: 16,
  },
  tab: {
    flex: 1,
    paddingVertical: 10,
    alignItems: 'center',
    borderRadius: 8,
  },
  activeTab: {
    backgroundColor: 'rgba(255, 255, 255, 0.12)',
  },
  tabText: {
    color: '#8E8E93',
    fontSize: 14,
    fontWeight: '600',
  },
  activeTabText: {
    color: '#FFFFFF',
  },
  tabContent: {
    gap: 16,
  },
  card: {
    backgroundColor: 'rgba(255, 255, 255, 0.05)',
    borderRadius: 16,
    padding: 16,
    borderWidth: 1,
    borderColor: 'rgba(255, 255, 255, 0.08)',
  },
});