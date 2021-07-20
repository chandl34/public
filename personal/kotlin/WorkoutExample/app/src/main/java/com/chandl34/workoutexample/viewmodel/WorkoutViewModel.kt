package com.chandl34.workoutexample.viewmodel

import android.os.CountDownTimer
import androidx.lifecycle.*
import com.chandl34.workoutexample.Const
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.domain.Workout
import com.chandl34.workoutexample.data.domain.WorkoutStep

class WorkoutViewModel(workout : Workout) : ViewModel() {
    //---- MEMBERS
    private val _workout = MutableLiveData<Workout>()
    private val _isPlaying = MutableLiveData<Boolean>()
    private var _timer : CountDownTimer? = null

    private val _stepTimeRemaining = MutableLiveData<Long>()
    val stepTimeRemaining : LiveData<Long>
        get() = _stepTimeRemaining

    private val _currentWorkoutStep = MutableLiveData<WorkoutStep?>()
    val currentWorkoutStep : LiveData<WorkoutStep?>
        get() = _currentWorkoutStep

    private val _remainingWorkoutSteps = MutableLiveData<List<WorkoutStep>>()
    val remainingWorkoutSteps : LiveData<List<WorkoutStep>>
        get() = _remainingWorkoutSteps

    val workoutIsValid = Transformations.map(_workout) { workout ->
        workout.steps.isNotEmpty()
    }

    val playButtonImageResource = Transformations.map(_isPlaying) { isPlaying ->
        if(isPlaying) R.drawable.baseline_pause_black_48 else R.drawable.baseline_play_arrow_black_48
    }

    private val _showWorkoutCompleteEvent = MutableLiveData<Boolean>()
    val showWorkoutCompleteEvent : LiveData<Boolean>
        get() = _showWorkoutCompleteEvent

    private val _navigateToWorkoutEditFragment = MutableLiveData<Workout?>()
    val navigateToWorkoutEditFragment : LiveData<Workout?>
        get() = _navigateToWorkoutEditFragment


    //---- CONSTRUCTORS
    init {
        updateWorkout(workout)
    }

    override fun onCleared() {
        super.onCleared()
        stopTimer()
    }


    //---- FACTORIES
    class Factory(private val workout : Workout) : ViewModelProvider.Factory {
        override fun <T : ViewModel?> create(modelClass : Class<T>) : T {
            if(modelClass.isAssignableFrom(WorkoutViewModel::class.java)) {
                return WorkoutViewModel(workout) as T
            }
            throw IllegalArgumentException("Unable to construct viewmodel")
        }
    }


    //---- METHODS
    fun updateWorkout(workout : Workout) {
        _workout.value = workout
        resetSteps()
    }

    fun onWorkoutCompleteEventShown() {
        _showWorkoutCompleteEvent.value = false
    }

    fun onWorkoutEditFragmentNavigatedTo() {
        _navigateToWorkoutEditFragment.value = null
    }

    private fun onStepComplete() {
        _remainingWorkoutSteps.value?.let { remainingWorkoutSteps ->
            if(remainingWorkoutSteps.isNotEmpty()) {
                val currentWorkoutStep = remainingWorkoutSteps[0]
                _stepTimeRemaining.value = currentWorkoutStep.duration
                _currentWorkoutStep.value = currentWorkoutStep
                _remainingWorkoutSteps.value = remainingWorkoutSteps.subList(1, remainingWorkoutSteps.size)
                startTimer(currentWorkoutStep.duration)
            }
            else {
                onWorkoutComplete()
            }
        }
    }

    private fun onWorkoutComplete() {
        resetSteps()
        _showWorkoutCompleteEvent.value = true
    }

    private fun resetSteps() {
        stopTimer()
        _stepTimeRemaining.value = 0
        _currentWorkoutStep.value = null
        _remainingWorkoutSteps.value = ArrayList(_workout.value?.steps)
    }

    private fun startTimer(seconds : Long) {
        _isPlaying.value = true

        _timer = object : CountDownTimer(seconds * Const.TIME_MILLISECONDS_IN_SECOND, Const.TIME_MILLISECONDS_IN_SECOND) {
            override fun onTick(millisUntilFinished : Long) {
                _stepTimeRemaining.value = millisUntilFinished / Const.TIME_MILLISECONDS_IN_SECOND
            }

            override fun onFinish() {
                onStepComplete()
            }
        }
        _timer?.start()
    }

    private fun stopTimer() {
        _isPlaying.value = false
        _timer?.cancel()
    }


    //---- ACTIONS
    fun pressedPlayPause() {
        val isPlaying = _isPlaying.value ?: return
        val stepTimeRemaining = _stepTimeRemaining.value ?: return

        if(isPlaying) {
            stopTimer()
        }
        else {
            if(stepTimeRemaining > 0) {
                startTimer(stepTimeRemaining)
            }
            else {
                onStepComplete()
            }
        }
    }

    fun pressedReset() {
        resetSteps()
    }

    fun pressedEdit() {
        stopTimer()
        _navigateToWorkoutEditFragment.value = _workout.value
    }
}