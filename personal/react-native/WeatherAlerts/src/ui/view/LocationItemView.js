import React from 'react';
import {Text, View, StyleSheet, TouchableHighlight} from 'react-native';

const LocationItemView = props => {
  //---- CONSTANTS
  const styles = StyleSheet.create({
    item: {
      padding: 8,
      minHeight: 66,
    },
    itemTitle: {
      fontSize: 20,
    },
    alert: {
      flexDirection: 'row',
      marginTop: 2,
    },
    alertType: {
      flex: 1,
      fontSize: 16,
    },
    alertDateTime: {
      fontSize: 14,
    },
  });

  //---- LAYOUT
  return (
    <View style={styles.item}>
      <Text style={styles.itemTitle}>{props.item.postcode}</Text>
      <View style={{marginTop: 6}}>
        {props.item.alerts && props.item.alerts.length ? (
          props.item.alerts.map(alert => _renderAlert(alert))
        ) : (
          <Text>No severe weather information</Text>
        )}
      </View>
    </View>
  );

  function _renderAlert(alert) {
    return (
      <View style={styles.alert}>
        <Text style={styles.alertType}>{alert.type}</Text>
        <Text
          style={[
            styles.alertDateTime,
            {color: _isDateSoon(alert.datetime) ? 'red' : 'black'},
          ]}>
          {alert.datetime}
        </Text>
      </View>
    );
  }

  //---- METHODS
  function _isDateSoon(datetime) {
    return (
      datetime.includes('08:00') ||
      datetime.includes('09:00') ||
      datetime.includes('10:00')
    );
  }
};

export default LocationItemView;
