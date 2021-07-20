package com.chandl34.workoutexample.util

import android.content.Context
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.WorkoutStepType


fun getWorkoutStepTypeName(context : Context, type : WorkoutStepType) : String {
    return when(type) {
        WorkoutStepType.PushUps -> context.getString(R.string.general_workout_step_type_push_ups)
        WorkoutStepType.SitUps -> context.getString(R.string.general_workout_step_type_sit_ups)
        WorkoutStepType.Burpees -> context.getString(R.string.general_workout_step_type_burpees)
        WorkoutStepType.JumpingJacks -> context.getString(R.string.general_workout_step_type_jumping_jacks)
        WorkoutStepType.Rest -> context.getString(R.string.general_workout_step_type_rest)
    }
}