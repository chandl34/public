package com.chandl34.workoutexample.data.entity

import java.io.Serializable

class Workout : Serializable {
    var steps: ArrayList<WorkoutStep>

    constructor() {
        steps = ArrayList()
    }

    constructor(other: Workout) {
        steps = ArrayList(other.steps)
    }
}