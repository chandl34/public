package com.chandl34.workoutexample.data.entity

import com.chandl34.workoutexample.Const.WorkoutStepType
import java.io.Serializable

class WorkoutStep(var type: WorkoutStepType, var duration: Int) : Serializable