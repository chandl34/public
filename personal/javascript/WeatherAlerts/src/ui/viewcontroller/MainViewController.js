import React from 'react';
import {
  Text,
  View,
  ScrollView,
  FlatList,
  Button,
  StyleSheet,
} from 'react-native';

const MainViewController = () => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    itemView: {
      padding: 8,
      minWidth: 100,
      minHeight: 44,
    },
  });

  //---- MEMBERS
  let data = [
    {title: 'A'},
    {title: 'B'},
    {title: 'C'},
  ];

  //---- LAYOUT
  const _renderItem = (item, index) => {
    return (
      <View style={styles.itemView}>
        <Text>{index} :: {item.title}</Text>
      </View>
    );
  };

  return (
    <View>
      <Text>{JSON.stringify({data})}</Text>
      <FlatList
      data={data}
      keyExtractor={(item, index) => index}
      renderItem={({item, index}) => _renderItem(item, index)} />
    </View>
  );
};

export default MainViewController;
