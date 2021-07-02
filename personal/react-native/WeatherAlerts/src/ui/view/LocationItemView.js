import React from 'react';
import {Text, View, StyleSheet, TouchableHighlight} from 'react-native';
import * as Format from 'date-fns';

import * as Const from 'src/Const.js';

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
    const date = Format.parseJSON(alert.datetime);

    return (
      <View style={styles.alert}>
        <Text style={styles.alertType}>{alert.type}</Text>
        <Text
          style={[
            styles.alertDateTime,
            {color: _isDateWithinWarningThreshold(date) ? 'red' : 'black'},
          ]}>
          {_getDateTimeString(date)}
        </Text>
      </View>
    );
  }

  //---- METHODS
  function _isDateWithinWarningThreshold(date) {
    const value = Format.differenceInHours(date, new Date());
    return value < Const.WARNING_THRESHOLD_IN_HOURS;
  }

  function _getDateTimeString(date) {
    return Format.format(date, Const.DATE_FORMAT_APP);
  }
};

export default LocationItemView;
