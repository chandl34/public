package com.chandl34.workoutexample.ui.view.adapter.general

import androidx.recyclerview.widget.RecyclerView
import java.util.*

abstract class BaseRecyclerViewAdapter<T, VH : RecyclerView.ViewHolder> : RecyclerView.Adapter<VH>() {
    //---- MEMBERS
    private var _data: MutableList<T>? = null

    //---- METHODS
    var data: MutableList<T>?
        get() = _data
        set(data) {
            _data = data
            notifyDataSetChanged()
        }

    fun getItem(position: Int): T {
        return _data!![position]
    }

    fun addItem(item: T) {
        if (_data == null) {
            _data = ArrayList()
        }
        insertItem(_data!!.size, item)
    }

    fun insertItem(index: Int, item: T) {
        if (_data == null) {
            return
        }
        _data!!.add(index, item)
        notifyItemInserted(index)
    }

    fun removeItem(position: Int) {
        if (_data == null) {
            return
        }
        _data!!.removeAt(position)
        notifyItemRemoved(position)
    }

    //---- RecyclerView.Adapter
    override fun getItemCount(): Int {
        return if (_data == null) {
            0
        } else _data!!.size
    }
}