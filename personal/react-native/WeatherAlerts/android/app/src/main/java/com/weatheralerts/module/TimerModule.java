package com.weatheralerts.module;


import android.os.CountDownTimer;
import android.util.Log;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;

import androidx.annotation.NonNull;


public class TimerModule
extends ReactContextBaseJavaModule
{
    //---- MEMBERS
    private CountDownTimer _timer;
    private long _millisInFuture;
    private long _countDownInterval;


    //---- CONSTRUCTORS
    public TimerModule(ReactApplicationContext context)
    {
        super(context);
    }


    //---- ReactContextBaseJavaModule
    @NonNull
    @Override
    public String getName()
    {
        return "TimerModule";
    }


    //---- METHODS
    @ReactMethod
    public void startTimer(double millisInFuture, double countDownInterval, Callback onTick, Callback onFinish)
    {
        _millisInFuture = (long)millisInFuture;
        _countDownInterval = (long)countDownInterval;
        Log.d(getName(), String.format("startTimer(%d, %d)", _millisInFuture, _countDownInterval));

        //_onTick = onTick;
        //onTick.invoke(789);
        //onFinish.invoke();

        _timer = new CountDownTimer(_millisInFuture, _countDownInterval)
        {
            @Override
            public void onTick(long millisUntilFinished)
            {
                //_onTick.invoke((double)millisUntilFinished);
            }

            @Override
            public void onFinish()
            {
               // onFinish.invoke();
            }
        };
        _timer.start();
/*

        _timer = object : CountDownTimer(seconds * Const.TIME_MILLISECONDS_IN_SECOND, Const.TIME_MILLISECONDS_IN_SECOND) {
            override fun onTick(millisUntilFinished : Long) {
                _stepTimeRemaining.value = millisUntilFinished / Const.TIME_MILLISECONDS_IN_SECOND
            }

            override fun onFinish() {
                onStepComplete()
            }
        }
 */
    }

    @ReactMethod
    private void stopTimer()
    {
        Log.d(getName(), String.format("stopTimer()"));
        /*
        if(_timer != null)
        {
            _timer.cancel();
        }

         */
    }
}
