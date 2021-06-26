import React, {Component} from 'react';
import {Text, View} from 'react-native';

class TestViewController extends Component {
  render() {
    return (
      <View
        style={{
          flex: 1,
          justifyContent: 'center',
          alignItems: 'center',
        }}>
        <Text>Goodbye, world!</Text>
      </View>
    );
  }
}

export default TestViewController;
