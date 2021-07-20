package com.chandl34.workoutexample.viewmodel

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.chandl34.workoutexample.data.domain.Workout
import com.chandl34.workoutexample.data.domain.WorkoutStep

class WorkoutEditViewModel(workout : Workout) : ViewModel() {
    //---- MEMBERS
    private val _workoutSteps = MutableLiveData<ArrayList<WorkoutStep>>()
    val workoutSteps : LiveData<ArrayList<WorkoutStep>>
        get() = _workoutSteps

    private val _navigateToWorkoutFragment = MutableLiveData<Workout?>()
    val navigateToWorkoutFragment : LiveData<Workout?>
        get() = _navigateToWorkoutFragment

    private val _navigateToWorkoutStepEditFragment = MutableLiveData<Boolean>()
    val navigateToWorkoutStepEditFragment : LiveData<Boolean>
        get() = _navigateToWorkoutStepEditFragment


    //---- CONSTRUCTORS
    init {
        _workoutSteps.value = ArrayList(workout.steps)
    }


    //---- FACTORIES
    class Factory(private val workout : Workout) : ViewModelProvider.Factory {
        override fun <T : ViewModel?> create(modelClass : Class<T>) : T {
            if(modelClass.isAssignableFrom(WorkoutEditViewModel::class.java)) {
                return WorkoutEditViewModel(workout) as T
            }
            throw IllegalArgumentException("Unable to construct viewmodel")
        }
    }


    //---- METHODS
    fun addWorkoutStep(workoutStep : WorkoutStep) {
        val workoutSteps = _workoutSteps.value ?: ArrayList()
        workoutSteps.add(workoutStep)
        _workoutSteps.value = workoutSteps
    }

    fun onWorkoutFragmentNavigatedTo() {
        _navigateToWorkoutFragment.value = null
    }

    fun onWorkoutStepEditFragmentNavigatedTo() {
        _navigateToWorkoutStepEditFragment.value = false
    }


    //---- ACTIONS
    fun pressedSave() {
        val workoutSteps = _workoutSteps.value ?: ArrayList()
        _navigateToWorkoutFragment.value = Workout(workoutSteps)
    }

    fun pressedDelete(workoutStep : WorkoutStep) {
        _workoutSteps.value?.let { workoutSteps ->
            workoutSteps.remove(workoutStep)
            _workoutSteps.value = workoutSteps
        }
    }

    fun pressedAddStep() {
        _navigateToWorkoutStepEditFragment.value = true
    }
}