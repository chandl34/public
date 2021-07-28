//
//  WorkoutEditViewController.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/27/21.
//

import UIKit


class WorkoutEditViewController: UIViewController
{
    typealias WorkoutEditAction = (Workout) -> Void
    
    
    // MARK: CONSTANTS
    static let showWorkoutStepEditSegueIdentifier = "ShowWorkoutStepEditSegue"
    
    
    // MARK: MEMBERS
    @IBOutlet var workoutStepsTableView: UITableView!
    
    private var _workoutSteps : Array<WorkoutStep> = Array()
    private var _editAction: WorkoutEditAction?
    
    private var _dataSource: WorkoutStepDataSource?
    
        
    // MARK: LIFE CYCLE
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        if(!_workoutSteps.isEmpty)
        {
            _workoutSteps.remove(at: Int.random(in: 0..<_workoutSteps.count))
        }
        
        updateWorkoutSteps(workoutSteps: _workoutSteps)
    }
    
    
    // MARK: METHODS
    func configure(with workout: Workout, editAction: WorkoutEditAction?)
    {
        _workoutSteps = workout.steps
        _editAction = editAction
    }
    
    private func updateWorkoutSteps(workoutSteps: Array<WorkoutStep>)
    {
        _workoutSteps = workoutSteps
        
        _dataSource = WorkoutStepDataSource(data: _workoutSteps)
        workoutStepsTableView.dataSource = _dataSource
    }
        
    
    // MARK: ACTIONS
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        if segue.identifier == Self.showWorkoutStepEditSegueIdentifier,
           let destination = segue.destination as? WorkoutStepEditViewController
        {
            destination.configure { workoutStep in
                self._workoutSteps.append(workoutStep)
                self.updateWorkoutSteps(workoutSteps: self._workoutSteps)
            }
        }
    }
    
    @IBAction func pressedCancel(_ sender: Any)
    {
        self.navigationController?.popViewController(animated: true)
    }
    
    @IBAction func pressedSave(_ sender: Any)
    {
        self.navigationController?.popViewController(animated: true)
        
        let workout = Workout(steps: _workoutSteps)
        _editAction?(workout)
    }
}

