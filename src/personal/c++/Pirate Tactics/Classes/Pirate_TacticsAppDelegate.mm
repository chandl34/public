//
//  Pirate_TacticsAppDelegate.mm
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "Pirate_TacticsAppDelegate.h"
#import "EAGLView.h"

@implementation Pirate_TacticsAppDelegate

@synthesize window;
@synthesize glView;

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
	[glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
