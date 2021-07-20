package com.chandl34.workoutexample.ui.adapters

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.chandl34.workoutexample.data.domain.WorkoutStep
import com.chandl34.workoutexample.databinding.ListItemWorkoutStepBinding
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class WorkoutStepAdapter(private val clickListener : ClickListener?) : ListAdapter<WorkoutStep, WorkoutStepAdapter.ViewHolder>(DiffCallback()) {
    //---- MEMBERS
    private val _adapterScope = CoroutineScope(Dispatchers.Default)


    //---- ListAdapter
    override fun onCreateViewHolder(parent : ViewGroup, viewType : Int) : ViewHolder {
        return ViewHolder.from(parent)
    }

    override fun onBindViewHolder(holder : ViewHolder, position : Int) {
        val item = getItem(position) as WorkoutStep
        holder.bind(item, clickListener)
    }


    //---- METHODS
    override fun submitList(list : List<WorkoutStep>?) {
        _adapterScope.launch {
            withContext(Dispatchers.Main) {
                super.submitList(list)
            }
        }
    }


    //---- RecyclerView.ViewHolder
    class ViewHolder private constructor(private val binding : ListItemWorkoutStepBinding) : RecyclerView.ViewHolder(binding.root) {
        fun bind(item : WorkoutStep, clickListener : ClickListener?) {
            binding.workoutStep = item
            binding.clickListener = clickListener
            binding.executePendingBindings()
        }

        companion object {
            fun from(parent : ViewGroup) : ViewHolder {
                val layoutInflater = LayoutInflater.from(parent.context)
                val binding = ListItemWorkoutStepBinding.inflate(layoutInflater, parent, false)
                return ViewHolder(binding)
            }
        }
    }


    //---- DiffCallback
    class DiffCallback : DiffUtil.ItemCallback<WorkoutStep>() {
        override fun areItemsTheSame(oldItem : WorkoutStep, newItem : WorkoutStep) : Boolean {
            return oldItem.id == newItem.id
        }

        @SuppressLint("DiffUtilEquals")
        override fun areContentsTheSame(oldItem : WorkoutStep, newItem : WorkoutStep) : Boolean {
            return oldItem == newItem
        }
    }


    //---- ClickListener
    class ClickListener(val clickListener : (workoutStep : WorkoutStep) -> Unit) {
        fun pressedDelete(workoutStep : WorkoutStep) = clickListener(workoutStep)
    }
}
