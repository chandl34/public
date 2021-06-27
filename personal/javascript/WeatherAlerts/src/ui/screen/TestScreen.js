import React, {Component} from 'react';
import {Text, View} from 'react-native';

class TestScreen extends Component {
  render() {
    return (
      <View
        style={{
          justifyContent: 'center',
          alignItems: 'center',
        }}>
        <Text>Goodbye, world!</Text>
      </View>
    );
  }
}

export default TestScreen;
