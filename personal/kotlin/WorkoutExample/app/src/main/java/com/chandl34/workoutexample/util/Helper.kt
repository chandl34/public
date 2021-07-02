package com.chandl34.workoutexample.util

import android.content.Context
import android.graphics.drawable.Drawable
import androidx.appcompat.content.res.AppCompatResources
import com.chandl34.workoutexample.Const.WorkoutStepType
import com.chandl34.workoutexample.R

object Helper {
    @JvmStatic
    fun getWorkoutStepTypeName(context: Context, type: WorkoutStepType): String {
        return when (type) {
            WorkoutStepType.PushUps -> context.getString(R.string.general_workout_step_type_push_ups)
            WorkoutStepType.SitUps -> context.getString(R.string.general_workout_step_type_sit_ups)
            WorkoutStepType.Burpees -> context.getString(R.string.general_workout_step_type_burpees)
            WorkoutStepType.JumpingJacks -> context.getString(R.string.general_workout_step_type_jumping_jacks)
            WorkoutStepType.Rest -> context.getString(R.string.general_workout_step_type_rest)
        }
    }

    @JvmStatic
    fun getWorkoutStepTypeDrawable(context: Context, type: WorkoutStepType): Drawable? {
        return when (type) {
            WorkoutStepType.PushUps -> AppCompatResources.getDrawable(context, R.drawable.step_type_push_ups)
            WorkoutStepType.SitUps -> AppCompatResources.getDrawable(context, R.drawable.step_type_sit_ups)
            WorkoutStepType.Burpees -> AppCompatResources.getDrawable(context, R.drawable.step_type_burpees)
            WorkoutStepType.JumpingJacks -> AppCompatResources.getDrawable(context, R.drawable.step_type_jumping_jacks)
            WorkoutStepType.Rest -> AppCompatResources.getDrawable(context, R.drawable.step_type_rest)
        }
    }
}