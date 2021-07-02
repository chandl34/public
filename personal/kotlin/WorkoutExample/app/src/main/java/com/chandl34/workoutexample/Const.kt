package com.chandl34.workoutexample

object Const {
    const val TIME_MILLISECONDS_IN_SECOND: Long = 1000

    enum class WorkoutStepType {
        PushUps, SitUps, Burpees, JumpingJacks, Rest
    }

    object RequestKey {
        const val EDIT_STEP = "EDIT_STEP"
    }

    object IntentKey {
        const val WORKOUT = "WORKOUT"
        const val WORKOUT_STEP = "WORKOUT_STEP"
    }
}