//
//  Const.swift
//  WorkoutExample
//
//  Created by Jonathan Chandler on 7/27/21.
//

import Foundation
import UIKit


enum WorkoutStepType
{
    case pushUps
    case sitUps
    case burpees
    case jumpingJacks
    case rest
    
    var description: String
    {
        switch self
        {
        case .pushUps:
            return "Push Ups"
        case .sitUps:
            return "Sit Ups"
        case .burpees:
            return "Burpees"
        case .jumpingJacks:
            return "Jumping Jacks"
        case .rest:
            return "Rest"
        }
    }
    
    var image: UIImage!
    {
        switch self
        {
        case .pushUps:
            return UIImage(named: "step_type_push_ups")
        case .sitUps:
            return UIImage(named: "step_type_sit_ups")
        case .burpees:
            return UIImage(named: "step_type_burpees")
        case .jumpingJacks:
            return UIImage(named: "step_type_jumping_jacks")
        case .rest:
            return UIImage(named: "step_type_rest")
        }
    }
}
