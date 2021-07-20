package com.chandl34.workoutexample

object Const {
    const val TIME_MILLISECONDS_IN_SECOND : Long = 1000
}

enum class WorkoutStepType {
    PushUps, SitUps, Burpees, JumpingJacks, Rest
}

object RequestKey {
    const val EDIT_WORKOUT = "EDIT_WORKOUT"
    const val EDIT_WORKOUT_STEP = "EDIT_WORKOUT_STEP"
}

object IntentKey {
    const val WORKOUT = "WORKOUT"
    const val WORKOUT_STEP = "WORKOUT_STEP"
}