package com.chandl34.workoutexample.ui

import android.widget.ImageView
import android.widget.TextView
import androidx.databinding.BindingAdapter
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.WorkoutStepType
import com.chandl34.workoutexample.data.domain.WorkoutStep
import com.chandl34.workoutexample.util.getWorkoutStepTypeName


@BindingAdapter("android:src")
fun setImageResource(imageView : ImageView, resId : Int) {
    imageView.setImageResource(resId)
}

@BindingAdapter("workout_step")
fun setWorkoutStep(imageView : ImageView, workoutStep : WorkoutStep?) {
    imageView.setImageResource(
            when(workoutStep?.type) {
                WorkoutStepType.PushUps -> R.drawable.step_type_push_ups
                WorkoutStepType.SitUps -> R.drawable.step_type_sit_ups
                WorkoutStepType.Burpees -> R.drawable.step_type_burpees
                WorkoutStepType.JumpingJacks -> R.drawable.step_type_jumping_jacks
                WorkoutStepType.Rest -> R.drawable.step_type_rest
                null -> 0
            })
}

@BindingAdapter("workout_step")
fun setWorkoutStep(textView : TextView, workoutStep : WorkoutStep?) {
    if(workoutStep == null) {
        textView.text = null
    }
    else {
        textView.text = getWorkoutStepTypeName(textView.context, workoutStep.type)
    }
}

@BindingAdapter("duration")
fun setDuration(textView : TextView, duration : Long) {
    val context = textView.context
    textView.text = context.getString(R.string.general_duration_format, duration)
}