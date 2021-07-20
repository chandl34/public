package com.chandl34.workoutexample.ui.fragment

import android.app.Dialog
import android.content.DialogInterface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.widget.AdapterView
import android.widget.Spinner
import androidx.appcompat.app.AlertDialog
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.DialogFragment
import androidx.lifecycle.ViewModelProvider
import com.chandl34.workoutexample.IntentKey
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.RequestKey
import com.chandl34.workoutexample.WorkoutStepType
import com.chandl34.workoutexample.data.domain.WorkoutStep
import com.chandl34.workoutexample.databinding.FragmentWorkoutStepEditBinding
import com.chandl34.workoutexample.ui.adapters.SingleChoiceSpinnerAdapter
import com.chandl34.workoutexample.util.getWorkoutStepTypeName
import com.chandl34.workoutexample.viewmodel.WorkoutStepEditViewModel
import com.google.android.material.slider.RangeSlider
import java.util.*

class WorkoutStepEditFragment : DialogFragment(), DialogInterface.OnShowListener {
    //---- MEMBERS
    private lateinit var _viewModel : WorkoutStepEditViewModel
    private lateinit var _binding : FragmentWorkoutStepEditBinding


    //---- LIFE CYCLE
    override fun onCreateDialog(savedInstanceState : Bundle?) : Dialog {
        _viewModel = ViewModelProvider(
                this,
                WorkoutStepEditViewModel.Factory()
        ).get(WorkoutStepEditViewModel::class.java)

        val inflater = LayoutInflater.from(context)
        _binding =
                DataBindingUtil.inflate(inflater, R.layout.fragment_workout_step_edit, null, false)
        _binding.viewModel = _viewModel

        val dialog = AlertDialog.Builder(requireActivity())
                .setTitle(R.string.screen_workout_step_edit_title)
                .setMessage(R.string.screen_workout_step_edit_message)
                .setView(_binding.root)
                .setPositiveButton(R.string.general_okay_button) { dialog, which -> _viewModel.pressedSave() }
                .setNeutralButton(R.string.general_cancel_button, null)
                .create()
        dialog.setOnShowListener(this)
        return dialog
    }


    //---- DialogInterface.OnShowListener
    override fun onShow(dialog : DialogInterface) {
        val alertDialog = dialog as AlertDialog
        val context = alertDialog.context

        _binding.lifecycleOwner = this

        _binding.durationSlider.addOnChangeListener(RangeSlider.OnChangeListener { slider, value, fromUser ->
            _viewModel.duration.value = value.toLong()
        })

        _binding.typeSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent : AdapterView<*>, view : View, position : Int, id : Long) {
                val spinner = parent as Spinner
                val option : Pair<String, WorkoutStepType> = spinner.selectedItem as Pair<String, WorkoutStepType>
                _viewModel.workoutStepType.value = option.second
            }

            override fun onNothingSelected(parent : AdapterView<*>?) {}
        }

        val optionList = ArrayList<Pair<String, WorkoutStepType>>()
        for(type in WorkoutStepType.values()) {
            val label = getWorkoutStepTypeName(context, type)
            optionList.add(Pair(label, type))
        }

        val adapter = SingleChoiceSpinnerAdapter<WorkoutStepType>()
        adapter.setData(optionList)
        _binding.typeSpinner.adapter = adapter

        _viewModel.navigateToWorkoutEditFragment.observe(this, { navigateToWorkoutEditFragment ->
            navigateToWorkoutEditFragment?.let { workoutStep ->
                navigateToWorkoutEditFragment(workoutStep)
                _viewModel.onWorkoutEditFragmentNavigatedTo()
            }
        })
    }


    //---- ACTIONS
    private fun navigateToWorkoutEditFragment(workoutStep : WorkoutStep) {
        val result = Bundle()
        result.putParcelable(IntentKey.WORKOUT_STEP, workoutStep)

        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResult(RequestKey.EDIT_WORKOUT_STEP, result)
    }
}