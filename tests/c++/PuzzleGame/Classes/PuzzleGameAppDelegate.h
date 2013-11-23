//
//  PuzzleGameAppDelegate.h
//  PuzzleGame
//
//  Created by Jonathan Chandler on 11/25/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PuzzleGameViewController;

@interface PuzzleGameAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    PuzzleGameViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet PuzzleGameViewController *viewController;

@end

