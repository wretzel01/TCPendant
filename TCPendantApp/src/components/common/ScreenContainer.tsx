import { View } from 'react-native';

export default function ScreenContainer({ children }) {
  return (
    <View
      style={{
        flex: 1,
        backgroundColor: '#0A0A0A',
        paddingHorizontal: 24,
        paddingTop: 60,
      }}
    >
      {children}
    </View>
  );
}
