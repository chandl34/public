//
//  ESRenderer.h
//  Pirate Tactics
//
//  Created by Jonathan Chandler on 2/14/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#ifndef ES_RENDERER_H_
#define ES_RENDERER_H_

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include "Include.h"

@protocol ESRenderer <NSObject>

- (void) render;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

- (void) push:(GLshort)t push:(const Coord2d<GLshort>&)p;
- (void) move:(GLshort)t move:(const Coord2d<GLshort>&)p;
- (void) release:(GLshort)t release:(const Coord2d<GLshort>&)p;

@end

#endif