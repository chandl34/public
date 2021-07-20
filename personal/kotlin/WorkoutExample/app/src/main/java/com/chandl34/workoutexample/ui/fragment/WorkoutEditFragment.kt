package com.chandl34.workoutexample.ui.fragment

import android.os.Bundle
import android.view.*
import androidx.databinding.DataBindingUtil
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.fragment.findNavController
import com.chandl34.workoutexample.IntentKey
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.RequestKey
import com.chandl34.workoutexample.data.domain.Workout
import com.chandl34.workoutexample.data.domain.WorkoutStep
import com.chandl34.workoutexample.databinding.FragmentWorkoutEditBinding
import com.chandl34.workoutexample.ui.adapters.WorkoutStepAdapter
import com.chandl34.workoutexample.viewmodel.WorkoutEditViewModel

class WorkoutEditFragment : Fragment() {
    //---- MEMBERS
    private lateinit var _viewModel : WorkoutEditViewModel


    //---- LIFE CYCLE
    override fun onCreateView(inflater : LayoutInflater, container : ViewGroup?, savedInstanceState : Bundle?) : View {
        setHasOptionsMenu(true)

        val arguments = WorkoutEditFragmentArgs.fromBundle(requireArguments())
        val workout = arguments.workout

        _viewModel = ViewModelProvider(this, WorkoutEditViewModel.Factory(workout)).get(WorkoutEditViewModel::class.java)

        val binding : FragmentWorkoutEditBinding =
                DataBindingUtil.inflate(inflater, R.layout.fragment_workout_edit, container, false)
        binding.lifecycleOwner = viewLifecycleOwner
        binding.viewModel = _viewModel

        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResultListener(RequestKey.EDIT_WORKOUT_STEP, viewLifecycleOwner, { requestKey, bundle ->
            val workoutStep = bundle.getParcelable(IntentKey.WORKOUT_STEP) as WorkoutStep?
            workoutStep?.let {
                _viewModel.addWorkoutStep(workoutStep)
            }
        })

        val adapter = WorkoutStepAdapter(WorkoutStepAdapter.ClickListener { workoutStep ->
            _viewModel.pressedDelete(workoutStep)
        })
        binding.stepsRecyclerView.adapter = adapter

        _viewModel.navigateToWorkoutFragment.observe(viewLifecycleOwner, { navigateToWorkoutFragment ->
            navigateToWorkoutFragment?.let { workout ->
                navigateToWorkoutFragment(workout)
                _viewModel.onWorkoutFragmentNavigatedTo()
            }
        })

        _viewModel.navigateToWorkoutStepEditFragment.observe(viewLifecycleOwner, { navigateToWorkoutStepEditFragment ->
            if(navigateToWorkoutStepEditFragment) {
                navigateToWorkoutStepEditFragment()
                _viewModel.onWorkoutStepEditFragmentNavigatedTo()
            }
        })

        _viewModel.workoutSteps.observe(viewLifecycleOwner, { workoutSteps ->
            adapter.submitList(ArrayList(workoutSteps))
        })

        return binding.root
    }

    override fun onCreateOptionsMenu(menu : Menu, inflater : MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.save, menu)
    }


    //---- METHODS
    private fun navigateToWorkoutFragment(workout : Workout) {
        val result = Bundle()
        result.putParcelable(IntentKey.WORKOUT, workout)

        val fragmentManager = parentFragmentManager
        fragmentManager.setFragmentResult(RequestKey.EDIT_WORKOUT, result)

        findNavController().navigate(WorkoutEditFragmentDirections.actionWorkoutEditFragmentToWorkoutFragment())
    }

    private fun navigateToWorkoutStepEditFragment() {
        findNavController().navigate(WorkoutEditFragmentDirections.actionWorkoutEditFragmentToWorkoutStepEditFragment())
    }


    //---- ACTIONS
    override fun onOptionsItemSelected(item : MenuItem) : Boolean {
        when(item.itemId) {
            R.id.save -> _viewModel.pressedSave()
        }

        return true
    }
}