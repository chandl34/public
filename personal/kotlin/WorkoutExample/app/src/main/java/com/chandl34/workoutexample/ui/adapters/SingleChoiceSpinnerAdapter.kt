package com.chandl34.workoutexample.ui.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.SpinnerAdapter
import android.widget.TextView

/**
 * Created by jmc on 8/24/17.
 */
class SingleChoiceSpinnerAdapter<T> : BaseAdapter(), SpinnerAdapter {
    //---- MEMBERS
    private var optionList : List<Pair<String, T>> = ArrayList()


    //---- METHODS
    fun setData(optionList : List<Pair<String, T>>) {
        this.optionList = optionList
        notifyDataSetChanged()
    }


    //---- BaseAdapter
    override fun getCount() : Int {
        return optionList.size
    }

    override fun getItem(position : Int) : Pair<String, T> {
        return optionList[position]
    }

    override fun getItemId(position : Int) : Long {
        return position.toLong()
    }

    override fun getView(position : Int, convertView : View?, parent : ViewGroup) : View {
        val convertView = if(convertView != null) {
            convertView
        }
        else {
            val inflater = LayoutInflater.from(parent.context)
            inflater.inflate(android.R.layout.simple_spinner_item, parent, false)
        }
        val item = getItem(position)

        // Get views
        val textView = convertView.findViewById<TextView>(android.R.id.text1)

        // Setup views
        textView.text = item.first
        return convertView
    }


    //---- SpinnerAdapter
    override fun getDropDownView(position : Int, convertView : View?, parent : ViewGroup) : View {
        val convertView = if(convertView != null) {
            convertView
        }
        else {
            val inflater = LayoutInflater.from(parent.context)
            inflater.inflate(android.R.layout.simple_spinner_dropdown_item, parent, false)
        }
        val item = getItem(position)

        // Get views
        val textView = convertView.findViewById<TextView>(android.R.id.text1)

        // Setup views
        textView.text = item.first
        return convertView
    }
}