package com.chandl34.workoutexample.ui.view.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.entity.WorkoutStep
import com.chandl34.workoutexample.ui.view.adapter.general.BaseRecyclerViewAdapter
import com.chandl34.workoutexample.util.Helper.getWorkoutStepTypeDrawable
import com.chandl34.workoutexample.util.Helper.getWorkoutStepTypeName

class WorkoutStepAdapter(private val _isEdit: Boolean) : BaseRecyclerViewAdapter<WorkoutStep, WorkoutStepAdapter.ViewHolder>() {

    //---- RecyclerView.Adapter
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val itemView = inflater.inflate(R.layout.adapter_workout_step, parent, false)
        return ViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = getItem(position)
        val context = holder.context
        holder.imageView.setImageDrawable(getWorkoutStepTypeDrawable(context, item.type))
        holder.typeTextView.text = getWorkoutStepTypeName(context, item.type)
        val duration = context.getString(R.string.general_duration_format, item.duration)
        holder.durationTextView.text = duration
    }

    //---- RecyclerView.ViewHolder
    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        var context: Context = itemView.context
        var imageView: ImageView = itemView.findViewById(R.id.image_view)
        var typeTextView: TextView = itemView.findViewById(R.id.type_text_view)
        var durationTextView: TextView = itemView.findViewById(R.id.duration_text_view)
        var removeButton: ImageButton = itemView.findViewById(R.id.remove_button)

        init {
            removeButton.visibility = if (_isEdit) View.VISIBLE else View.GONE
            removeButton.setOnClickListener {
                val position = adapterPosition
                if (position != RecyclerView.NO_POSITION) {
                    removeItem(position)
                }
            }
        }
    }
}