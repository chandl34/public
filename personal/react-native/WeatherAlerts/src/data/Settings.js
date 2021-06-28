/*
import AsyncStorage from '@react-native-async-storage/async-storage';

//---- CONSTANTS
const KEY_UUID = 'KEY_UUID';

//---- MEMBERS
export const UUID = async () => {
  try {
    const value = await AsyncStorage.getItem(KEY_UUID);
    return value !== null ? value : 'not there!';
  } catch (e) {
    return 'error';
  }
};

/*
const Settings = () => {
  //---- CONSTANTS
  const KEY_UUID = 'KEY_UUID';

  //---- MEMBERS
  const UUID = async () => {
    try {
        const value = await AsyncStorage.getItem(KEY_UUID);
        return value !== null ? value : "not there!";
    } catch (e) {}
  };
};

export default Settings;
*/
