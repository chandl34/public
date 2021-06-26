import React, {Component} from 'react';
import {Text, View, Button} from 'react-native';

class MainViewController extends Component {
  render() {
    const {navigation} = this.props;

    return (
      <View
        style={{
          flex: 1,
          justifyContent: 'center',
          alignItems: 'center',
        }}>
        <Text>Hello, world!</Text>
        <Button
          title="Next"
          onPress={() => navigation.navigate('TestViewController')}
        />
      </View>
    );
  }
}

export default MainViewController;
