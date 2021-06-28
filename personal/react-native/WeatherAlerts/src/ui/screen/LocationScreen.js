import React from 'react';
import {Text, StyleSheet, View} from 'react-native';

const LocationScreen = ({navigation, route}) => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    screen: {
      flex: 1,
      padding: 8,
      alignItems: 'center',
      justifyContent: 'center',
    },
  });

  //---- LAYOUT
  return (
    <View style={styles.screen}>
      <Text>{JSON.stringify(route.params.item)}</Text>
    </View>
  );
};

export default LocationScreen;
