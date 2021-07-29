import React, {useState, useEffect} from 'react';
import {
  Text,
  SafeAreaView,
  View,
  FlatList,
  Button,
  StyleSheet,
  TouchableHighlight,
  PixelRatio,
  NativeModules,
} from 'react-native';
import SQLite from 'react-native-sqlite-storage';
import AsyncStorage from '@react-native-async-storage/async-storage';
import UUID from 'react-native-uuid';

import LocationScreen from 'src/ui/screen/LocationScreen.js';
import LocationItemView from 'src/ui/view/LocationItemView.js';
import TimerModule from 'src/module/TimerModule.tsx';
import * as Const from 'src/Const.js';


SQLite.DEBUG(true);
SQLite.enablePromise(true);

const MainScreen = ({navigation}) => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    screen: {},
    list: {
      height: '100%',
    },
    listHeader: {
      padding: 8,
      fontSize: 18,
      fontWeight: 'bold',
    },
    listSeparator: {
      height: 1,
      backgroundColor: '#aaaaaa',
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
      <FlatList
        style={styles.list}
        data={data}
        keyExtractor={(item, index) => index.toString()}
        ItemSeparatorComponent={() => _renderSeparator()}
        ListHeaderComponent={() => _renderHeader()}
        renderItem={({item, index, separators}) =>
          _renderItem(item, index, separators)
        }
      />
    </SafeAreaView>
  );

  function _renderSeparator() {
    return <View style={styles.listSeparator} />;
  }

  function _renderHeader() {
    return <Text style={styles.listHeader}>Monitored Locations</Text>;
  }

  function _renderItem(item, index, separators) {
    return (
      <TouchableHighlight
        style={{backgroundColor: '#e7e7e7'}}
        underlayColor="#dddddd"
        onPress={() => _pressedItem(item, index)}
        onShowUnderlay={separators.highlight}
        onHideUnderlay={separators.unhighlight}>
        <LocationItemView item={item} />
      </TouchableHighlight>
    );
  }

  //---- ACTIONS
  function _pressedItem(item, index) {
    if(index == 0)
    TimerModule.startTimer(
      15 * 1000,
      1 * 1000,
      (millisUntilFinished) => {
        console.log(`onTick(${millisUntilFinished})`);
      },
      () => {
        console.log(`onFinish()`);
      });
    else if(index == 1)
    TimerModule.stopTimer();
    //navigation.navigate('LocationScreen', {item: item});
  }

  //---- METHODS
  function _refreshData(uuid) {
    console.log(`UUID:  ${uuid}`);

    // TODO build server and database

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

    _requestGetAlerts(uuid);
  }

  //---- REQUESTS
  function _requestGetAlerts(uuid) {
    const url =
      `${Const.API_METHOD_ALERTS}?` +
      `uuid=${encodeURIComponent(uuid)}&` +
      `debug=${encodeURIComponent(Const.DEBUG_ALERTS)}`;
    const options = {method: 'GET'};

    console.log(`REQUEST\n${options.method} ${url}`);
    fetch(url, options)
      .then(response => response.json())
      .then(json => {
        console.log(`RESPONSE\n${JSON.stringify(json)}`);
        if (json.error != null) {
          alert(json.error);
          return;
        }

        setData(json.data);
      })
      .catch(e => alert(e.message));
  }
};

export default MainScreen;
