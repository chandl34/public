//
//  EAGLView.mm
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "EAGLView.h"
#import "ES1Renderer.h"

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

Coord2d<GLshort> screenPixel;

// You must implement this method
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithCoder:(NSCoder*)coder
{    
    if ((self = [super initWithCoder:coder]))
	{
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		// Compatible only with ES 1.1
		renderer = [[ES1Renderer alloc] init];
			
		if (!renderer)
		{
			[self release];
			return nil;
		}
        
		animating = FALSE;
		displayLinkSupported = FALSE;
		animationFrameInterval = 1;
		displayLink = nil;
		animationTimer = nil;
		
		// My stuff
		[self setMultipleTouchEnabled:YES];
		touch[0] = NULL;
		touch[1] = NULL;
		touchCount = 0;
		
		// A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
		// class is used as fallback when it isn't available.
		NSString *reqSysVer = @"3.1";
		NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
		if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
			displayLinkSupported = TRUE;
    }
	
    return self;
}

- (void) drawView:(id)sender
{
    [renderer render];
}

- (void) layoutSubviews
{
	[renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (NSInteger) animationFrameInterval
{
	return animationFrameInterval;
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void) startAnimation
{
	if (!animating)
	{
		if (displayLinkSupported)
		{
			// CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
			// if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
			// not be called in system versions earlier than 3.1.

			displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setFrameInterval:animationFrameInterval];
			[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		if (displayLinkSupported)
		{
			[displayLink invalidate];
			displayLink = nil;
		}
		else
		{
			[animationTimer invalidate];
			animationTimer = nil;
		}
		
		animating = FALSE;
	}
}

- (void) dealloc
{
    [renderer release];	
    [super dealloc];
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event{
	NSArray* array = [touches allObjects];	
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; i++){
		touchTemp = [array objectAtIndex:i];
		
		if(touchCount >= 2)
			return;
	
		if(touch[0] == NULL)	
			t = 0;
		else
			t = 1;		
		touch[t] = touchTemp;
		
		CGPoint touchLoc = [touch[t] locationInView:self];	
		touchCount++;
		
		screenPixel[X] = touchLoc.y;
		screenPixel[Y] = touchLoc.x;
		[renderer push: t push:screenPixel];
	}
}


- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event{
	NSArray* array = [touches allObjects];
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; i++){
		touchTemp = [array objectAtIndex:i];
		for(t = 0; t < 2; t++){			// Find the matching touch in the array
			if(touchTemp == touch[t])
				break;
		}		
		if(t == 2)						// Return if touch was not found
			continue;
		
		CGPoint touchLoc = [touch[t] locationInView:self];	
		
		screenPixel[X] = touchLoc.y;
		screenPixel[Y] = touchLoc.x;
		[renderer move:t move:screenPixel];
	}
}


- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event{		
	NSArray* array = [touches allObjects];
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; i++){
		touchTemp = [array objectAtIndex:i];
		for(t = 0; t < 2; t++){			// Find the matching touch in the array
			if(touchTemp == touch[t])
				break;
		}		
		if(t == 2)						// Return if touch was not found
			continue;				
				
		CGPoint touchLoc = [touch[t] locationInView:self];
		
		touch[t] = NULL;
		touchCount--;
				
		screenPixel[X] = touchLoc.y;
		screenPixel[Y] = touchLoc.x;
		[renderer release:t release:screenPixel];				
	}
}


- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event{
	printf("Touch cancelled\n");
	[self touchesEnded:touches withEvent: event];
}

@end
