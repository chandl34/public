package com.chandl34.workoutexample.ui.view

import android.graphics.Rect
import android.view.View
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.ItemDecoration

class GridItemDecoration(private val _dividerLength: Int) : ItemDecoration() {
    override fun getItemOffsets(outRect: Rect, view: View, parent: RecyclerView, state: RecyclerView.State) {
        outRect.left = _dividerLength / 2
        outRect.right = _dividerLength / 2 + _dividerLength % 2
        outRect.top = _dividerLength / 2
        outRect.bottom = _dividerLength / 2 + _dividerLength % 2
    }
}