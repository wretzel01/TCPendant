import { ScrollView } from 'react-native';

export default function ScreenContainer({ children }) {
  return (
    <ScrollView
      contentContainerStyle={{
        padding: 20,
        paddingBottom: 40,
      }}
    >
      {children}
    </ScrollView>
  );
}
