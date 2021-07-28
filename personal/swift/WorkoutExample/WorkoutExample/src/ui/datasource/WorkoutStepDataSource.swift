//
//  WorkoutStepDataSource.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/28/21.
//

import UIKit


class WorkoutStepDataSource: NSObject
{
    private var _data: Array<WorkoutStep>

    
    init(data: Array<WorkoutStep>)
    {
        _data = data
        super.init()
    }
}


extension WorkoutStepDataSource: UITableViewDataSource
{
    static let workoutStepCellIdentifier = "WorkoutStepCell"
    
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int
    {
        return _data.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell = tableView.dequeueReusableCell(withIdentifier: Self.workoutStepCellIdentifier, for: indexPath)
        
        let step = _data[indexPath.row]
        
        cell.textLabel?.text = step.type.description
        cell.imageView?.image = step.type.image
        cell.detailTextLabel?.text = String(format: "%d s", step.duration)
        
        return cell
    }
}
