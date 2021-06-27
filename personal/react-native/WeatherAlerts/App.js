/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import {NavigationContainer} from '@react-navigation/native';
import {createStackNavigator} from '@react-navigation/stack';

import MainScreen from 'src/ui/screen/MainScreen.js';
import TestScreen from 'src/ui/screen/TestScreen.js';

const Stack = createStackNavigator();

const App = () => {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen
          name="MainScreen"
          component={MainScreen}
          options={{title: 'Main'}}
        />
        <Stack.Screen
          name="TestScreen"
          component={TestScreen}
          options={{title: 'Test'}}
        />
      </Stack.Navigator>
    </NavigationContainer>
  );
};

export default App;
