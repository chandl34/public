import React, {useState, useEffect} from 'react';
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
  PixelRatio,
} from 'react-native';
import SQLite from 'react-native-sqlite-storage';
import AsyncStorage from '@react-native-async-storage/async-storage';
import UUID from 'react-native-uuid';

//import * as Settings from 'src/data/Settings.js';
import TestScreen from 'src/ui/screen/TestScreen.js';
import * as Const from 'src/Const.js';

SQLite.DEBUG(true);
SQLite.enablePromise(true);

const MainScreen = () => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    screen: {},
    list: {},
    listSeparator: {
      height: 1,
      backgroundColor: '#aaaaaa',
    },
    item: {
      padding: 8,
      minHeight: 66,
      backgroundColor: '#e7e7e7',
    },
  });

  //---- MEMBERS
  const [uuid, setUUID] = useState(null);
  const [data, setData] = useState([]);
  const [message, setMessage] = useState(null);

  //---- EVENTS
  useEffect(() => {
    setData([]); // TODO remove
    setUUID(null); // TODO remove
    setMessage(null); // TODO remove

    AsyncStorage.getItem(Const.KEY_UUID)
      .then(value => {
        if (value !== null) {
          setUUID(value);
          _refreshData(value);
          return;
        }

        value = UUID.v4();
        AsyncStorage.setItem(Const.KEY_UUID, value)
          .then(() => {
            setUUID(value);
            _refreshData(value);
          })
          .catch(e => alert(e.message));
      })
      .catch(e => alert(e.message));
  }, []);

  //---- LAYOUT
  return (
    <SafeAreaView style={styles.screen}>
      <Text style={{padding: 8, textAlign: 'center'}}>{message}</Text>
      <FlatList
        style={{height: '100%'}}
        data={data}
        keyExtractor={(item, index, separators) => index}
        ItemSeparatorComponent={() => _renderSeparator()}
        renderItem={({item, index, separators}) =>
          _renderItem(item, index, separators)
        }
      />
    </SafeAreaView>
  );

  function _renderSeparator() {
    return <View style={styles.listSeparator} />;
  }

  function _renderItem(item, index, separators) {
    return (
      <TouchableHighlight
        style={styles.item}
        underlayColor="#dddddd"
        onPress={() => _pressedItem(item, index, separators)}
        onShowUnderlay={separators.highlight}
        onHideUnderlay={separators.unhighlight}>
        <Text>{item.label}</Text>
      </TouchableHighlight>
    );
  }

  //---- ACTIONS
  function _pressedItem(item, index, separators) {}

  //---- METHODS
  function _refreshData(uuid) {
    // TODO read from database
    /*
    setMessage('Plugin integrity check ...');
    SQLite.echoTest()
      .then(() => {
        setMessage('Integrity check passed ...');
        setMessage('Opening database ...');
        SQLite.openDatabase(Const.DB_NAME, Const.DB_VERSION, Const.DB_DISPLAY_NAME, Const.DB_SIZE)
        .then((db) => {


          db.close()
          .then(status => {setMessage('Database closed.')})
          .catch(e => alert(e.message));
        })
        .catch(e => alert(e.message));
      })
      .catch(e => alert(e.message));
      */
    // TODO make server request

    //alert(uuid);
    //*
    setTimeout(() => {
      setData([{label: 'A'}, {label: 'B'}, {label: 'C'}]);
    }, 1000);
    //*/

    //const db = SQLite.openDatabase("test.db", "1.0", "Test Database", 200000, openCB, errorCB);
  }

  //---- REQUESTS
  function _requestData(uuid) {}
};

export default MainScreen;
