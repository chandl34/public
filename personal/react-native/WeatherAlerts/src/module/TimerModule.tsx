import { NativeModules } from 'react-native';
const { TimerModule } = NativeModules;

interface TimerInterface {
   startTimer(
     millisInFuture: number,
     countDownInterval: number,
     onTick: (millisUntilFinished: number) => void,
     onFinish: () => void): void;
   stopTimer(): void;
}
export default TimerModule as TimerInterface;
