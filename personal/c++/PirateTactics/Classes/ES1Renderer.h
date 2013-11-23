//
//  ES1Renderer.h
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#ifndef ES1_RENDERER_H_
#define ES1_RENDERER_H_

#include "BaseScreen.h"
#import "ESRenderer.h"

@interface ES1Renderer : NSObject <ESRenderer>
{
@private
	EAGLContext *context;
	
	// The pixel dimensions of the CAEAGLLayer
	GLint backingWidth;
	GLint backingHeight;
	
	// The OpenGL names for the framebuffer and renderbuffer used to render to this view
	GLuint defaultFramebuffer, colorRenderbuffer;
	
	bool valid;
	BaseScreen* baseScreen;
}

- (void) setup;
- (void) render;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

- (void) push:(GLshort)t push:(const Coord2d<GLshort>&)p;
- (void) move:(GLshort)t move:(const Coord2d<GLshort>&)p;
- (void) release:(GLshort)t release:(const Coord2d<GLshort>&)p;

@end

#endif