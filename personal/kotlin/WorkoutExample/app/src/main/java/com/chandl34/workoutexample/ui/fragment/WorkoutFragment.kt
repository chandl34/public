package com.chandl34.workoutexample.ui.fragment

import android.content.Context
import android.os.Bundle
import android.os.CountDownTimer
import android.view.*
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AlertDialog
import androidx.core.content.res.ResourcesCompat
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.chandl34.workoutexample.Const
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.entity.WorkoutStep
import com.chandl34.workoutexample.data.viewmodel.WorkoutViewModel
import com.chandl34.workoutexample.ui.view.GridItemDecoration
import com.chandl34.workoutexample.ui.view.adapter.WorkoutStepAdapter
import com.chandl34.workoutexample.util.Helper.getWorkoutStepTypeDrawable
import com.chandl34.workoutexample.util.Helper.getWorkoutStepTypeName
import com.chandl34.workoutexample.util.Util.dpToPx
import java.util.*

class WorkoutFragment : Fragment() {
    //---- INTERFACES
    interface OnSelectionListener {
        fun onWorkoutEditSelected()
    }

    //---- MEMBERS
    private var _viewModel: WorkoutViewModel? = null
    private var _isPlaying = false
    private var _stepIndex = 0
    private var _stepTimeRemaining: Long = 0
    private var _stepImageView: ImageView? = null
    private var _stepTypeTextView: TextView? = null
    private var _stepTimerTextView: TextView? = null
    private var _playPauseButton: ImageButton? = null
    private var _resetButton: ImageButton? = null
    private var _recyclerView: RecyclerView? = null
    private var _timer: CountDownTimer? = null
    private var _onSelectionListener: OnSelectionListener? = null

    //---- LIFE CYCLE
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)
        val args = arguments
        if (args != null) {
        }
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val context = requireContext()
        val view = inflater.inflate(R.layout.fragment_workout, container, false)
        _stepImageView = view.findViewById(R.id.step_image_view)
        _stepTypeTextView = view.findViewById(R.id.step_type_text_view)
        _stepTimerTextView = view.findViewById(R.id.step_timer_text_view)
        _playPauseButton = view.findViewById(R.id.play_pause_button)
        _resetButton = view.findViewById(R.id.reset_button)
        _recyclerView = view.findViewById(R.id.steps_recycler_view)
        _playPauseButton?.setOnClickListener { pressedPlayPause() }
        _resetButton?.setOnClickListener { pressedReset() }
        _recyclerView?.layoutManager = LinearLayoutManager(context)
        _recyclerView?.addItemDecoration(GridItemDecoration(dpToPx(context, 1f).toInt()))
        return view
    }

    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.edit, menu)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        _viewModel = ViewModelProvider(requireActivity()).get(WorkoutViewModel::class.java)
        _viewModel?.item?.observe(requireActivity(), { resetSteps() })
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        _onSelectionListener = try {
            context as OnSelectionListener
        } catch (e: ClassCastException) {
            throw ClassCastException(context.toString() + " must implement " + this.javaClass.canonicalName + ".OnSelectionListener")
        }
    }

    override fun onStop() {
        super.onStop()
        stopTimer()
        updateLayout()
    }

    //---- ACTIONS
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (item.itemId == R.id.edit) {
            pressedEdit()
            return true
        }
        return super.onOptionsItemSelected(item)
    }

    private fun pressedEdit() {
        _onSelectionListener?.onWorkoutEditSelected()
    }

    private fun pressedPlayPause() {
        if (_isPlaying) {
            stopTimer()
        } else {
            _isPlaying = true
            if (_stepTimeRemaining > 0) {
                startTimer(_stepTimeRemaining)
            } else {
                val workout = _viewModel!!.item.value
                if (_stepIndex >= workout!!.steps.size) {
                    resetSteps()
                }
                onStepComplete()
            }
        }
        updateLayout()
    }

    private fun pressedReset() {
        resetSteps()
    }

    //---- METHODS
    private fun getStep(index: Int): WorkoutStep? {
        val workout = _viewModel!!.item.value
        return if (index >= 0 && index < workout!!.steps.size) {
            workout.steps[index]
        } else null
    }

    private fun startTimer(seconds: Long) {
        _timer = object : CountDownTimer(seconds * Const.TIME_MILLISECONDS_IN_SECOND, Const.TIME_MILLISECONDS_IN_SECOND) {
            override fun onTick(millisUntilFinished: Long) {
                _stepTimeRemaining = millisUntilFinished / Const.TIME_MILLISECONDS_IN_SECOND
                val text = getString(R.string.general_duration_format, _stepTimeRemaining)
                _stepTimerTextView!!.text = text
            }

            override fun onFinish() {
                onStepComplete()
            }
        }
        _timer?.start()
    }

    private fun stopTimer() {
        _isPlaying = false
        if (_timer != null) {
            _timer!!.cancel()
            _timer = null
        }
    }

    private fun onStepComplete() {
        ++_stepIndex
        val adapter = _recyclerView!!.adapter as WorkoutStepAdapter?
        if (adapter!!.itemCount > 0) {
            adapter.removeItem(0)
        }
        val step = getStep(_stepIndex)
        _isPlaying = step != null
        _stepTimeRemaining = step?.duration?.toLong() ?: 0.toLong()
        updateLayout()
        if (step != null) {
            startTimer(step.duration.toLong())
        } else {
            val workout = _viewModel!!.item.value
            if (_stepIndex >= workout!!.steps.size) {
                onWorkoutComplete()
            }
        }
    }

    private fun onWorkoutComplete() {
        AlertDialog.Builder(requireActivity())
                .setTitle(R.string.screen_workout_workout_complete_title)
                .setMessage(R.string.screen_workout_workout_complete_message)
                .setPositiveButton(R.string.general_okay_button, null)
                .show()
    }

    private fun resetSteps() {
        stopTimer()
        val workout = _viewModel!!.item.value
        val adapter = WorkoutStepAdapter(false)
        adapter.data = ArrayList(workout!!.steps)
        _recyclerView?.adapter = adapter
        _stepIndex = -1
        _stepTimeRemaining = 0
        updateLayout()
    }

    private fun updateLayout() {
        val context = requireContext()
        val workout = _viewModel!!.item.value
        val hasSteps = workout!!.steps.size > 0
        val step = getStep(_stepIndex)
        val typeDrawable = if (step != null) getWorkoutStepTypeDrawable(context, step.type) else null
        _stepImageView?.setImageDrawable(typeDrawable)
        val typeText = if (step != null) getWorkoutStepTypeName(context, step.type) else getString(R.string.screen_workout_step_type_text_step_not_set_text)
        _stepTypeTextView?.text = typeText
        val timerText = if (step != null) getString(R.string.general_duration_format, _stepTimeRemaining) else getString(R.string.screen_workout_step_timer_text_step_not_set_text)
        _stepTimerTextView?.text = timerText
        val resID = if (_isPlaying) R.drawable.baseline_pause_black_48 else R.drawable.baseline_play_arrow_black_48
        _playPauseButton?.setImageDrawable(ResourcesCompat.getDrawable(resources, resID, null))
        _playPauseButton?.isEnabled = hasSteps
        _resetButton!!.isEnabled = hasSteps
    }

    companion object {
        //---- FACTORIES
        @JvmStatic
        fun newInstance(): WorkoutFragment {
            val fragment = WorkoutFragment()
            val args = Bundle()
            fragment.arguments = args
            return fragment
        }
    }
}