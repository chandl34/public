package com.chandl34.workoutexample.ui.fragment

import android.app.Dialog
import android.content.DialogInterface
import android.content.DialogInterface.OnShowListener
import android.os.Bundle
import android.util.Pair
import android.view.View
import android.widget.AdapterView
import android.widget.AdapterView.OnItemSelectedListener
import android.widget.Spinner
import androidx.appcompat.app.AlertDialog
import androidx.fragment.app.DialogFragment
import com.chandl34.workoutexample.Const.IntentKey
import com.chandl34.workoutexample.Const.RequestKey
import com.chandl34.workoutexample.Const.WorkoutStepType
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.entity.WorkoutStep
import com.chandl34.workoutexample.ui.view.adapter.general.SingleChoiceSpinnerAdapter
import com.chandl34.workoutexample.util.Helper.getWorkoutStepTypeName
import com.google.android.material.slider.RangeSlider
import java.util.*

class WorkoutStepEditFragment : DialogFragment(), OnShowListener {
    //---- MEMBERS
    private var _type: WorkoutStepType? = null
    private var _duration = 0

    //---- LIFE CYCLE
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (arguments != null) {
        }

        val context = requireContext()
        _type = WorkoutStepType.PushUps
        _duration = context.resources.getInteger(R.integer.min_workout_step_duration)
    }

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        val dialog = AlertDialog.Builder(requireActivity())
                .setTitle(R.string.screen_workout_step_edit_title)
                .setMessage(R.string.screen_workout_step_edit_message)
                .setView(R.layout.fragment_workout_step_edit)
                .setPositiveButton(R.string.general_okay_button) { dialog, which -> pressedSave() }
                .setNeutralButton(R.string.general_cancel_button, null)
                .create()
        dialog.setOnShowListener(this)
        return dialog
    }

    //---- DialogInterface.OnShowListener
    override fun onShow(dialog: DialogInterface) {
        val alertDialog = dialog as AlertDialog
        val context = alertDialog.context
        val typeSpinner = alertDialog.findViewById<Spinner>(R.id.type_spinner)
        val durationSlider = alertDialog.findViewById<RangeSlider>(R.id.duration_slider)
        val optionList: MutableList<Pair<String, WorkoutStepType>> = ArrayList()
        for (type in WorkoutStepType.values()) {
            val label = getWorkoutStepTypeName(context, type)
            optionList.add(Pair.create(label, type))
        }
        typeSpinner!!.onItemSelectedListener = object : OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>, view: View, position: Int, id: Long) {
                val spinner = parent as Spinner
                val option: Pair<String, WorkoutStepType> = spinner.selectedItem as Pair<String, WorkoutStepType>
                _type = option.second
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {}
        }
        val adapter = SingleChoiceSpinnerAdapter<WorkoutStepType>()
        adapter.setData(optionList)
        typeSpinner.adapter = adapter
        durationSlider!!.addOnChangeListener(RangeSlider.OnChangeListener { slider, value, fromUser -> _duration = value.toInt() })
    }

    //---- ACTIONS
    private fun pressedSave() {
        val result = Bundle()
        result.putSerializable(IntentKey.WORKOUT_STEP, WorkoutStep(_type!!, _duration))
        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResult(RequestKey.EDIT_STEP, result)
    }

    companion object {
        //---- FACTORIES
        @JvmStatic
        fun newInstance(): WorkoutStepEditFragment {
            val fragment = WorkoutStepEditFragment()
            val args = Bundle()
            fragment.arguments = args
            return fragment
        }
    }
}