//
//  PuzzleGameViewController.h
//  PuzzleGame
//
//  Created by Jonathan Chandler on 11/25/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "MainScreen.h"


@interface PuzzleGameViewController : UIViewController
{
	EAGLContext *context;
	GLuint program;
	
	BOOL animating;
	NSInteger animationFrameInterval;
	CADisplayLink *displayLink;
	
@private
	MainScreen* mainScreen;
	
	UITouch* touch[2];
	int touchCount;
	Coord2d<GLshort> touchedPixel;
}

- (void) setup;

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end
