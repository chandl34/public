package com.chandl34.workoutexample.viewmodel

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.chandl34.workoutexample.WorkoutStepType
import com.chandl34.workoutexample.data.domain.WorkoutStep

class WorkoutStepEditViewModel : ViewModel() {
    //---- MEMBERS
    val workoutStepType = MutableLiveData<WorkoutStepType>()
    val duration = MutableLiveData<Long>()

    private val _navigateToWorkoutEditFragment = MutableLiveData<WorkoutStep?>()
    val navigateToWorkoutEditFragment : LiveData<WorkoutStep?>
        get() = _navigateToWorkoutEditFragment


    //---- FACTORIES
    class Factory : ViewModelProvider.Factory {
        override fun <T : ViewModel?> create(modelClass : Class<T>) : T {
            if(modelClass.isAssignableFrom(WorkoutStepEditViewModel::class.java)) {
                return WorkoutStepEditViewModel() as T
            }
            throw IllegalArgumentException("Unable to construct viewmodel")
        }
    }

    //---- METHODS
    fun onWorkoutEditFragmentNavigatedTo() {
        _navigateToWorkoutEditFragment.value = null
    }


    //---- ACTIONS
    fun pressedSave() {
        val currTime = System.currentTimeMillis()
        val type = workoutStepType.value ?: WorkoutStepType.PushUps
        val duration = duration.value ?: 1

        _navigateToWorkoutEditFragment.value = WorkoutStep(currTime, type, duration)
    }
}