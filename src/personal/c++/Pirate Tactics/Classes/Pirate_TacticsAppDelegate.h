//
//  Pirate_TacticsAppDelegate.h
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#ifndef APP_DELEGATE_H_
#define APP_DELEGATE_H_

#import <UIKit/UIKit.h>

@class EAGLView;

@interface Pirate_TacticsAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    EAGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;

@end

#endif
