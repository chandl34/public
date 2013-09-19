//
//  TacticsAppDelegate.m
//  Tactics
//
//  Created by Jonathan Chandler on 2/2/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#import "TacticsAppDelegate.h"
#import "EAGLView.h"

@implementation TacticsAppDelegate

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
