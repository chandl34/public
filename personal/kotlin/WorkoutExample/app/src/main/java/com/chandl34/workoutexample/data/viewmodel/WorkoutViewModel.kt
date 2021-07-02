package com.chandl34.workoutexample.data.viewmodel

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.chandl34.workoutexample.data.entity.Workout

class WorkoutViewModel : ViewModel() {
    private val _item = MutableLiveData<Workout>()
    val item: LiveData<Workout>
        get() = _item

    fun setItem(workout: Workout) {
        _item.value = workout
    }
}