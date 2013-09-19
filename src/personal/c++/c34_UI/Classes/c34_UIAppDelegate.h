//
//  c34_UIAppDelegate.h
//  c34_UI
//
//  Created by Jonathan Chandler on 1/24/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class c34_UIViewController;

@interface c34_UIAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    c34_UIViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet c34_UIViewController *viewController;

@end

