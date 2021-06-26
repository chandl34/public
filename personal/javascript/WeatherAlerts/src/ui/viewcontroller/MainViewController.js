import React from 'react';
import {
  Text,
  SafeAreaView,
  View,
  ScrollView,
  FlatList,
  Button,
  StyleSheet,
  Pressable,
  TouchableHighlight,
} from 'react-native';

const MainViewController = () => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    screen: {},
    list: {height: '100%'},
    item: {
      padding: 8,
      minHeight: 66,
      backgroundColor: '#e7e7e7',
    },
  });

  //---- MEMBERS
  let data = [{label: 'A'}, {label: 'B'}, {label: 'C'}];

  //---- LAYOUT
  return (
    <SafeAreaView style={styles.screen}>
      <FlatList
        style={styles.list}
        data={data}
        keyExtractor={(item, index) => index}
        renderItem={({item, index}) => _renderItem(item, index)}
      />
    </SafeAreaView>
  );

  function _renderItem(item, index) {
    return (
      <TouchableHighlight
        style={styles.item}
        underlayColor="#dddddd"
        onPress={() => _pressedItem(item, index)}>
        <Text>{item.label}</Text>
      </TouchableHighlight>
    );
  }

  //---- ACTIONS
  function _pressedItem(item, index) {}
};

export default MainViewController;
