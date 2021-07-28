//
//  MainViewController.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/27/21.
//

import UIKit

class WorkoutViewController: UIViewController
{
    // MARK: MEMBERS
    @IBOutlet var playPauseButton: UIButton!
    @IBOutlet var resetButton: UIButton!
    @IBOutlet var stepTypeImageView: UIImageView!
    @IBOutlet var stepTypeLabel: UILabel!
    @IBOutlet var stepDurationLabel: UILabel!
    @IBOutlet var upcomingStepsTableView: UITableView!
     
    private var _workout: Workout?
    private var _isPlaying: Bool = false
    private var _stepTimeRemaining: Int = 0
    private var _currentStep: WorkoutStep?
    private var _upcomingSteps: Array<WorkoutStep> = Array()
    
    
    // MARK: LIFE CYCLE
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        var steps = Array<WorkoutStep>()
        steps.append(WorkoutStep(id: 1, type: .sitUps, duration: 10))
        steps.append(WorkoutStep(id: 2, type: .rest, duration: 15))
        steps.append(WorkoutStep(id: 3, type: .jumpingJacks, duration: 10))
        _workout = Workout(steps: steps)
        
        print("%@", _workout?.steps[0].type)
    }
    
    
    // MARK: ACTIONS
    @IBAction func pressedPlayPause(_ sender: Any)
    {
        
    }
    
    @IBAction func pressedReset(_ sender: Any)
    {
        
    }
}

