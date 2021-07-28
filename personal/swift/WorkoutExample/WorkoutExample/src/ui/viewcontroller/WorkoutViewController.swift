//
//  MainViewController.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/27/21.
//

import UIKit

class WorkoutViewController: UIViewController
{
    // MARK: CONSTANTS
    static let showWorkoutEditSegueIdentifier = "ShowWorkoutEditSegue"
    
    
    // MARK: MEMBERS
    @IBOutlet var playPauseButton: UIButton!
    @IBOutlet var resetButton: UIButton!
    @IBOutlet var stepTypeImageView: UIImageView!
    @IBOutlet var stepTypeLabel: UILabel!
    @IBOutlet var stepDurationLabel: UILabel!
    @IBOutlet var upcomingStepsTableView: UITableView!
     
    private var _timer: Timer?
    
    private var _workout: Workout = Workout(steps: Array())
    private var _isPlaying: Bool = false
    private var _stepTimeRemaining: Int = 0
    private var _currentWorkoutStep: WorkoutStep?
    private var _remainingWorkoutSteps: Array<WorkoutStep> = Array()
    
    private var _dataSource: WorkoutStepDataSource?
    
    
    // MARK: LIFE CYCLE
    deinit
    {
        _timer?.invalidate()
    }
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        var steps = Array<WorkoutStep>()
        steps.append(WorkoutStep(id: 1, type: .sitUps, duration: 10))
        steps.append(WorkoutStep(id: 2, type: .rest, duration: 15))
        steps.append(WorkoutStep(id: 3, type: .jumpingJacks, duration: 10))
        let workout = Workout(steps: steps)
        updateWorkout(workout: workout)
    }
    
    
    // MARK: METHODS
    private func updateWorkout(workout: Workout)
    {
        _workout = workout
        resetSteps()
        
        playPauseButton.isEnabled = !_workout.steps.isEmpty
        resetButton.isEnabled = !_workout.steps.isEmpty
    }
    
    private func updateCurrentWorkoutStep(workoutStep: WorkoutStep?)
    {
        _currentWorkoutStep = workoutStep
        
        stepDurationLabel.isHidden = _currentWorkoutStep == nil
        
        stepTypeLabel.text = workoutStep?.type.description
        stepTypeImageView.image = workoutStep?.type.image
    }
    
    private func updateStepTimeRemaining(stepTimeRemaining: Int)
    {
        _stepTimeRemaining = stepTimeRemaining
        
        stepDurationLabel.text = String(format: "%d s", _stepTimeRemaining)
    }
    
    private func updateRemainingWorkoutSteps(remainingWorkoutSteps: Array<WorkoutStep>)
    {
        _remainingWorkoutSteps = remainingWorkoutSteps
        
        _dataSource = WorkoutStepDataSource(data: _remainingWorkoutSteps)
        upcomingStepsTableView.dataSource = _dataSource
        upcomingStepsTableView.reloadData()
    }
    
    private func updateIsPlaying(isPlaying: Bool)
    {
        _isPlaying = isPlaying
        
        let image = _isPlaying ? UIImage(named: "pause") : UIImage(named: "play")
        playPauseButton.setImage(image, for: .normal)
    }
    
    private func resetSteps()
    {
        stopTimer()
        updateStepTimeRemaining(stepTimeRemaining: 0)
        updateCurrentWorkoutStep(workoutStep: nil)
        updateRemainingWorkoutSteps(remainingWorkoutSteps: Array(_workout.steps))
    }
    
    private func onStepComplete()
    {
        if(!_remainingWorkoutSteps.isEmpty)
        {
            let currentWorkoutStep = _remainingWorkoutSteps[0]
            updateStepTimeRemaining(stepTimeRemaining: currentWorkoutStep.duration)
            updateCurrentWorkoutStep(workoutStep: currentWorkoutStep)
            updateRemainingWorkoutSteps(remainingWorkoutSteps: Array(_remainingWorkoutSteps.dropFirst()))
            startTimer(seconds: currentWorkoutStep.duration)
        }
        else
        {
            onWorkoutComplete()
        }
    }
    
    private func onWorkoutComplete()
    {
        resetSteps()
        // TODO show dialog
    }
    
    private func startTimer(seconds: Int)
    {
        updateIsPlaying(isPlaying: true)
            
        updateStepTimeRemaining(stepTimeRemaining: seconds)
        _timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: { timer in
            if(self._stepTimeRemaining > 0)
            {
                self.updateStepTimeRemaining(stepTimeRemaining: self._stepTimeRemaining - 1)
            }
            else
            {
                timer.invalidate()
                self.onStepComplete()
            }
        })
    }
    
    private func stopTimer()
    {
        updateIsPlaying(isPlaying: false)
        _timer?.invalidate()
    }
    
    
    // MARK: ACTIONS
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        if segue.identifier == Self.showWorkoutEditSegueIdentifier,
           let destination = segue.destination as? WorkoutEditViewController
        {
            destination.configure(with: _workout) { workout in
                self.updateWorkout(workout: workout)
            }
        }
    }
    
    @IBAction func pressedPlayPause(_ sender: Any)
    {
        if(_isPlaying)
        {
            stopTimer()
        }
        else
        {
            if(_stepTimeRemaining > 0)
            {
                startTimer(seconds: _stepTimeRemaining)
            }
            else
            {
                onStepComplete()
            }
        }
    }
    
    @IBAction func pressedReset(_ sender: Any)
    {
        resetSteps()
    }
}

