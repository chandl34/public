package com.chandl34.workoutexample.ui.fragment

import android.os.Bundle
import android.view.*
import androidx.appcompat.app.AlertDialog
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.fragment.findNavController
import com.chandl34.workoutexample.IntentKey
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.RequestKey
import com.chandl34.workoutexample.data.domain.Workout
import com.chandl34.workoutexample.databinding.FragmentWorkoutBinding
import com.chandl34.workoutexample.ui.adapters.WorkoutStepAdapter
import com.chandl34.workoutexample.viewmodel.WorkoutViewModel

class WorkoutFragment : Fragment() {
    //---- MEMBERS
    private lateinit var _viewModel : WorkoutViewModel


    //---- LIFE CYCLE
    override fun onCreateView(inflater : LayoutInflater, container : ViewGroup?, savedInstanceState : Bundle?) : View {
        setHasOptionsMenu(true)

        //val arguments = getArguments()WorkoutFragmentArgs.fromBundle(requireArguments())

        _viewModel = ViewModelProvider(this, WorkoutViewModel.Factory(Workout())).get(WorkoutViewModel::class.java)

        val binding : FragmentWorkoutBinding =
                DataBindingUtil.inflate(inflater, R.layout.fragment_workout, container, false)
        binding.lifecycleOwner = viewLifecycleOwner
        binding.viewModel = _viewModel

        val adapter = WorkoutStepAdapter(null)
        binding.stepsRecyclerView.adapter = adapter

        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResultListener(RequestKey.EDIT_WORKOUT, viewLifecycleOwner, { requestKey, bundle ->
            val workout = bundle.getParcelable(IntentKey.WORKOUT) as Workout?
            workout?.let {
                _viewModel.updateWorkout(workout)
            }
        })

        _viewModel.navigateToWorkoutEditFragment.observe(viewLifecycleOwner, { navigateToWorkoutEditFragment ->
            navigateToWorkoutEditFragment?.let { workout ->
                navigateToWorkoutEditFragment(workout)
                _viewModel.onWorkoutEditFragmentNavigatedTo()
            }
        })

        _viewModel.showWorkoutCompleteEvent.observe(viewLifecycleOwner, { showWorkoutCompleteEvent ->
            if(showWorkoutCompleteEvent) {
                showWorkoutCompleteEvent()
                _viewModel.onWorkoutCompleteEventShown()
            }
        })

        _viewModel.remainingWorkoutSteps.observe(viewLifecycleOwner, { remainingWorkoutSteps ->
            adapter.submitList(remainingWorkoutSteps)
        })

        return binding.root
    }

    override fun onCreateOptionsMenu(menu : Menu, inflater : MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.edit, menu)
    }


    //---- METHODS
    private fun navigateToWorkoutEditFragment(workout : Workout) {
        findNavController().navigate(WorkoutFragmentDirections.actionWorkoutFragmentToWorkoutEditFragment(workout))
    }

    private fun showWorkoutCompleteEvent() {
        AlertDialog.Builder(requireActivity())
                .setTitle(R.string.screen_workout_workout_complete_title)
                .setMessage(R.string.screen_workout_workout_complete_message)
                .setPositiveButton(R.string.general_okay_button, null)
                .show()
    }


    //---- ACTIONS
    override fun onOptionsItemSelected(item : MenuItem) : Boolean {
        when(item.itemId) {
            R.id.edit -> _viewModel.pressedEdit()
        }

        return true
    }
}