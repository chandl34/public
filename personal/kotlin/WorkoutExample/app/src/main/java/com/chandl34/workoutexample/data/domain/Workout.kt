package com.chandl34.workoutexample.data.domain

import android.os.Parcelable
import kotlinx.android.parcel.Parcelize

@Parcelize
data class Workout(val steps : ArrayList<WorkoutStep> = ArrayList()) : Parcelable