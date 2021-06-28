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
import LocationScreen from 'src/ui/screen/LocationScreen.js';

const Stack = createStackNavigator();

const App = () => {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen
          name="MainScreen"
          component={MainScreen}
          options={{title: 'Alerts'}}
        />
        <Stack.Screen
          name="LocationScreen"
          component={LocationScreen}
          options={{title: 'Location'}}
        />
      </Stack.Navigator>
    </NavigationContainer>
  );
};

export default App;
