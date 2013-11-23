//
//  PuzzleGameViewController.m
//  PuzzleGame
//
//  Created by Jonathan Chandler on 11/25/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "PuzzleGameViewController.h"
#import "EAGLView.h"

// Uniform index.
enum {
	UNIFORM_TRANSLATE,
	NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
	ATTRIB_VERTEX,
	ATTRIB_COLOR,
	NUM_ATTRIBUTES
};

@interface PuzzleGameViewController ()
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
@end

@implementation PuzzleGameViewController

@synthesize animating, context, displayLink;

- (void)awakeFromNib
{
	//    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	
	//    if (!aContext)
	//    {
	EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	//    }
	
	if (!aContext)
		NSLog(@"Failed to create ES context");		
	else if (![EAGLContext setCurrentContext:aContext])
		NSLog(@"Failed to set ES context current");
	
	self.context = aContext;
	[aContext release];
	
	[(EAGLView *)self.view setContext:context];
	[(EAGLView *)self.view setFramebuffer];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();
	
	if ([context API] == kEAGLRenderingAPIOpenGLES2)
		[self loadShaders];
	
	[self setup];
	
	animating = FALSE;
	animationFrameInterval = 1;
	self.displayLink = nil;
}

- (void)setup
{	
	[[UIApplication sharedApplication] setStatusBarHidden:YES animated:YES]; 
	if(mainScreen == NULL)
		mainScreen = new MainScreen();	
}


- (void)dealloc
{
	if (program)
	{
		glDeleteProgram(program);
		program = 0;
	}
	
	// Tear down context.
	if ([EAGLContext currentContext] == context)
		[EAGLContext setCurrentContext:nil];
	
	[context release];
	
	delete mainScreen;
	
	[super dealloc];
}

- (void)viewWillAppear:(BOOL)animated
{
	[self startAnimation];
	
	[super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[self stopAnimation];
	
	[super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
	if (program)
	{
		glDeleteProgram(program);
		program = 0;
	}
	
	// Tear down context.
	if ([EAGLContext currentContext] == context)
		[EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
	return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
	/*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
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

- (void)startAnimation
{
	if (!animating)
	{
		CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawFrame)];
		[aDisplayLink setFrameInterval:animationFrameInterval];
		[aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
		
		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		[self.displayLink invalidate];
		self.displayLink = nil;
		animating = FALSE;
	}
}

- (void)drawFrame
{
	[(EAGLView *)self.view setFramebuffer];
	
	mainScreen->draw();
	
	[(EAGLView *)self.view presentFramebuffer];
}

- (void)didReceiveMemoryWarning
{
	// Releases the view if it doesn't have a superview.
	[super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc. that aren't in use.
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
	GLint status;
	const GLchar *source;
	
	source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
	if (!source)
	{
		NSLog(@"Failed to load vertex shader");
		return FALSE;
	}
	
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
	
#if defined(DEBUG)
	GLint logLength;
	glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetShaderInfoLog(*shader, logLength, &logLength, log);
		NSLog(@"Shader compile log:\n%s", log);
		free(log);
	}
#endif
	
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		glDeleteShader(*shader);
		return FALSE;
	}
	
	return TRUE;
}

- (BOOL)linkProgram:(GLuint)prog
{
	GLint status;
	
	glLinkProgram(prog);
	
#if defined(DEBUG)
	GLint logLength;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
		NSLog(@"Program link log:\n%s", log);
		free(log);
	}
#endif
	
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0)
		return FALSE;
	
	return TRUE;
}

- (BOOL)validateProgram:(GLuint)prog
{
	GLint logLength, status;
	
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
		NSLog(@"Program validate log:\n%s", log);
		free(log);
	}
	
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	if (status == 0)
		return FALSE;
	
	return TRUE;
}

- (BOOL)loadShaders
{
	GLuint vertShader, fragShader;
	NSString *vertShaderPathname, *fragShaderPathname;
	
	// Create shader program.
	program = glCreateProgram();
	
	// Create and compile vertex shader.
	vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
	if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname])
	{
		NSLog(@"Failed to compile vertex shader");
		return FALSE;
	}
	
	// Create and compile fragment shader.
	fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
	if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname])
	{
		NSLog(@"Failed to compile fragment shader");
		return FALSE;
	}
	
	// Attach vertex shader to program.
	glAttachShader(program, vertShader);
	
	// Attach fragment shader to program.
	glAttachShader(program, fragShader);
	
	// Bind attribute locations.
	// This needs to be done prior to linking.
	glBindAttribLocation(program, ATTRIB_VERTEX, "position");
	glBindAttribLocation(program, ATTRIB_COLOR, "color");
	
	// Link program.
	if (![self linkProgram:program])
	{
		NSLog(@"Failed to link program: %d", program);
		
		if (vertShader)
		{
			glDeleteShader(vertShader);
			vertShader = 0;
		}
		if (fragShader)
		{
			glDeleteShader(fragShader);
			fragShader = 0;
		}
		if (program)
		{
			glDeleteProgram(program);
			program = 0;
		}
		
		return FALSE;
	}
	
	// Get uniform locations.
	uniforms[UNIFORM_TRANSLATE] = glGetUniformLocation(program, "translate");
	
	// Release vertex and fragment shaders.
	if (vertShader)
		glDeleteShader(vertShader);
	if (fragShader)
		glDeleteShader(fragShader);
	
	return TRUE;
}



// Touch related
- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event{
	NSArray* array = [touches allObjects];	
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; ++i){
		touchTemp = [array objectAtIndex:i];
		
		if(touchCount >= 2)
			return;
		
		if(touch[0] == NULL)	
			t = 0;
		else
			t = 1;		
		touch[t] = touchTemp;
		
		CGPoint touchLoc = [touch[t] locationInView:(EAGLView *)self.view];	
		++touchCount;
		
		touchedPixel[X] = touchLoc.y;
		touchedPixel[Y] = touchLoc.x;
		mainScreen->push(t, touchedPixel);
	}
}


- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event{
	NSArray* array = [touches allObjects];
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; ++i){
		touchTemp = [array objectAtIndex:i];
		for(t = 0; t < 2; ++t){			// Find the matching touch in the array
			if(touchTemp == touch[t])
				break;
		}		
		if(t == 2)						// Return if touch was not found
			continue;
		
		CGPoint touchLoc = [touch[t] locationInView:(EAGLView *)self.view];	
		
		touchedPixel[X] = touchLoc.y;
		touchedPixel[Y] = touchLoc.x;
		mainScreen->move(t, touchedPixel);
	}
}


- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event{	
	NSArray* array = [touches allObjects];
	UITouch* touchTemp;	
	int t;
	for(int i = 0; i < [array count]; ++i){
		touchTemp = [array objectAtIndex:i];
		for(t = 0; t < 2; ++t){			// Find the matching touch in the array
			if(touchTemp == touch[t])
				break;
		}		
		if(t == 2)						// Return if touch was not found
			continue;				
		
		CGPoint touchLoc = [touch[t] locationInView:(EAGLView *)self.view];
		
		touch[t] = NULL;
		--touchCount;
		
		touchedPixel[X] = touchLoc.y;
		touchedPixel[Y] = touchLoc.x;
		mainScreen->release(t, touchedPixel);
	}
}


- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event{
	printf("Touch cancelled\n");
	[self touchesEnded:touches withEvent: event];
}


@end
