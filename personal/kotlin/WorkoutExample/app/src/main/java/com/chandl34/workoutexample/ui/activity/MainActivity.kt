package com.chandl34.workoutexample.ui.activity

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import com.chandl34.workoutexample.R
import com.chandl34.workoutexample.data.entity.Workout
import com.chandl34.workoutexample.data.viewmodel.WorkoutViewModel
import com.chandl34.workoutexample.ui.fragment.WorkoutEditFragment
import com.chandl34.workoutexample.ui.fragment.WorkoutEditFragment.Companion.newInstance
import com.chandl34.workoutexample.ui.fragment.WorkoutFragment
import com.chandl34.workoutexample.ui.fragment.WorkoutFragment.Companion.newInstance

class MainActivity : AppCompatActivity(), WorkoutFragment.OnSelectionListener, WorkoutEditFragment.OnSelectionListener {
    //---- MEMBERS
    private var _viewModel: WorkoutViewModel? = null

    //---- LIFE CYCLE
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        _viewModel = ViewModelProvider(this).get(WorkoutViewModel::class.java)

        // Test setup
        if (savedInstanceState == null) {
            val fragment: Fragment = newInstance(null)
            pushFragment(fragment, null, true)
        }
    }

    //---- FRAGMENTS
    private fun pushFragment(fragment: Fragment, tag: String? = null, addToBackStack: Boolean = true) {
        val fragmentManager = supportFragmentManager
        val fragmentTransaction = fragmentManager.beginTransaction()
        val topFragment = topFragment
        if (topFragment == null) {
            fragmentTransaction.add(R.id.fragment_container, fragment, tag)
        } else {
            fragmentTransaction.replace(R.id.fragment_container, fragment, tag)
            if (addToBackStack) {
                fragmentTransaction.addToBackStack(tag)
            }
        }
        fragmentTransaction.commit()
    }

    private fun popFragment() {
        val fragmentManager = supportFragmentManager
        fragmentManager.popBackStack()
    }

    private val topFragment: Fragment?
        private get() {
            val fragmentManager = supportFragmentManager
            return fragmentManager.findFragmentById(R.id.fragment_container)
        }

    //---- WorkoutFragment.OnSelectionListener
    override fun onWorkoutEditSelected() {
        val workout = _viewModel!!.item.value
        val fragment: Fragment = newInstance(Workout(workout!!))
        pushFragment(fragment, null, true)
    }

    //---- WorkoutEditFragment.OnSelectionListener
    override fun onWorkoutEdited(workout: Workout) {
        _viewModel!!.setItem(workout)
        val fragmentManager = supportFragmentManager
        val wasRoot = fragmentManager.backStackEntryCount == 0
        popFragment()
        if (wasRoot) {
            val fragment: Fragment = newInstance()
            pushFragment(fragment, null, false)
        }
    }
}