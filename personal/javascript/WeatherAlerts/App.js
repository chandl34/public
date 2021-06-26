/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import 'react-native-gesture-handler';

import React, {Component} from 'react';
import {NavigationContainer} from '@react-navigation/native';
import {createStackNavigator} from '@react-navigation/stack';

import MainViewController from './src/ui/viewcontroller/MainViewController.js';
import TestViewController from './src/ui/viewcontroller/TestViewController.js';

const Stack = createStackNavigator();

class App extends Component {
  render() {
    return (
      <NavigationContainer>
        <Stack.Navigator>
          <Stack.Screen
            name="MainViewController"
            component={MainViewController}
            options={{title: 'Main'}}
          />
          <Stack.Screen
            name="TestViewController"
            component={TestViewController}
            options={{title: 'Test'}}
          />
        </Stack.Navigator>
      </NavigationContainer>
    );
  }
}

export default App;
