//
//  CountingGameAppDelegate.h
//  CountingGame
//
//  Created by Jonathan Chandler on 11/25/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CountingGameViewController;

@interface CountingGameAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    CountingGameViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet CountingGameViewController *viewController;

@end

