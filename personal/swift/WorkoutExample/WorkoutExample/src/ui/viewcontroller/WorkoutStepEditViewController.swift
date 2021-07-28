//
//  WorkoutStepEditViewController.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/27/21.
//

import UIKit


class WorkoutStepEditViewController: UIViewController
{
    typealias WorkoutStepEditAction = (WorkoutStep) -> Void
    
    
    // MARK: MEMBERS
    private var _editAction: WorkoutStepEditAction?
    
    
    // MARK: LIFE CYCLE
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        
    }
    
    
    // MARK: METHODS
    func configure(editAction: WorkoutStepEditAction?)
    {
        _editAction = editAction
    }
                
    
    // MARK: ACTIONS
    @IBAction func pressedCancel(_ sender: Any)
    {
        self.navigationController?.popViewController(animated: true)
    }
    
    @IBAction func pressedSave(_ sender: Any)
    {
        self.navigationController?.popViewController(animated: true)
        
        let currTime = Int(Date().timeIntervalSince1970)
        let duration = Int.random(in: 1...10)
        let type = WorkoutStepType.allCases[Int.random(in: 0..<WorkoutStepType.allCases.count)]
        let workoutStep = WorkoutStep(id: currTime, type: type, duration: duration)
        
        _editAction?(workoutStep)
    }
}

