import { View, Text } from 'react-native';

export default function ConnectionBanner({ connected }) {
  return (
    <View
      style={{
        backgroundColor: connected ? '#1E8F4D' : '#8F1E1E',
        padding: 12,
        borderRadius: 8,
        marginBottom: 24,
      }}
    >
      <Text style={{ color: 'white', fontSize: 18, textAlign: 'center' }}>
        {connected ? 'Connected to TCPendant' : 'Connecting…'}
      </Text>
    </View>
  );
}
