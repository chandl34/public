
 import React, { Component } from 'react';
 import { Text, View } from 'react-native';


 class MainViewController extends Component {
   render() {
     return (
       <View style={{
           flex: 1,
           justifyContent: "center",
           alignItems: "center"
         }}>
         <Text>Testing, world!</Text>
       </View>
     );
   }
 }

export default MainViewController;
