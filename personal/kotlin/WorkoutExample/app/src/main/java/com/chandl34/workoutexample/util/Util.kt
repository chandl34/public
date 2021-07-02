package com.chandl34.workoutexample.util

import android.content.Context

object Util {
    @JvmStatic
    fun dpToPx(context: Context, dp: Float): Float {
        return dp * context.resources.displayMetrics.density
    }
}