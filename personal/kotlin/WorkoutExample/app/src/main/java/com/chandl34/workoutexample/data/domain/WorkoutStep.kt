package com.chandl34.workoutexample.data.domain

import android.os.Parcelable
import com.chandl34.workoutexample.WorkoutStepType
import kotlinx.android.parcel.Parcelize

@Parcelize
data class WorkoutStep(val id : Long, val type : WorkoutStepType, val duration : Long) : Parcelable