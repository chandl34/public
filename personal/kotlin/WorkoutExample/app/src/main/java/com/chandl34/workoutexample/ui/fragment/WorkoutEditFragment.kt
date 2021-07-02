package com.chandl34.workoutexample.ui.fragment

import android.content.Context
import android.os.Bundle
import android.view.*
import android.widget.Button
import androidx.fragment.app.DialogFragment
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.chandl34.workoutexample.Const.IntentKey
import com.chandl34.workoutexample.Const.RequestKey
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.entity.Workout
import com.chandl34.workoutexample.data.entity.WorkoutStep
import com.chandl34.workoutexample.ui.fragment.WorkoutStepEditFragment.Companion.newInstance
import com.chandl34.workoutexample.ui.view.GridItemDecoration
import com.chandl34.workoutexample.ui.view.adapter.WorkoutStepAdapter
import com.chandl34.workoutexample.util.Util.dpToPx

class WorkoutEditFragment : Fragment() {
    //---- INTERFACES
    interface OnSelectionListener {
        fun onWorkoutEdited(workout: Workout)
    }

    //---- MEMBERS
    private var _workout: Workout? = null
    private var _recyclerView: RecyclerView? = null
    private var _onSelectionListener: OnSelectionListener? = null

    //---- LIFE CYCLE
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)
        val args = arguments
        if (args != null) {
            _workout = args.getSerializable(IntentKey.WORKOUT) as Workout?
        }
        if (_workout == null) {
            _workout = Workout()
        }
        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResultListener(RequestKey.EDIT_STEP, this, { requestKey, bundle ->
            val step = bundle.getSerializable(IntentKey.WORKOUT_STEP) as WorkoutStep?
            val adapter = _recyclerView!!.adapter as WorkoutStepAdapter?
            adapter!!.addItem(step!!)
        })
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val context = requireContext()
        val view = inflater.inflate(R.layout.fragment_workout_edit, container, false)
        _recyclerView = view.findViewById(R.id.steps_recycler_view)
        val addStepButton = view.findViewById<Button>(R.id.add_step_button)
        _recyclerView?.layoutManager = LinearLayoutManager(context)
        _recyclerView?.addItemDecoration(GridItemDecoration(dpToPx(context, 1f).toInt()))
        val adapter = WorkoutStepAdapter(true)
        adapter.data = _workout?.steps
        _recyclerView?.adapter = adapter
        addStepButton.setOnClickListener { pressedAddStep() }
        return view
    }

    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.save, menu)
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        _onSelectionListener = try {
            context as OnSelectionListener
        } catch (e: ClassCastException) {
            throw ClassCastException(context.toString() + " must implement " + this.javaClass.canonicalName + ".OnSelectionListener")
        }
    }

    //---- ACTIONS
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (item.itemId == R.id.save) {
            pressedSave()
            return true
        }
        return super.onOptionsItemSelected(item)
    }

    private fun pressedSave() {
        if (_workout != null) {
            _onSelectionListener?.onWorkoutEdited(_workout!!)
        }
    }

    private fun pressedAddStep() {
        val fragment: DialogFragment = newInstance()
        fragment.show(parentFragmentManager, null)
    }

    companion object {
        //---- FACTORIES
        @JvmStatic
        fun newInstance(workout: Workout?): WorkoutEditFragment {
            val fragment = WorkoutEditFragment()
            val args = Bundle()
            args.putSerializable(IntentKey.WORKOUT, workout)
            fragment.arguments = args
            return fragment
        }
    }
}