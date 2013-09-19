/*
 *  Drawable.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "Include.h"


struct TexAttr{
	GLuint _texName;
	GLuint _texCoordName;
	GLuint _texVertName;
};


class Drawable{	
public:
	virtual void draw(bool, TexAttr* = NULL) = 0;	
};


class DrawableMaskable{	
public:
	virtual void draw(bool, bool) = 0;	
};

#endif DRAWABLE_H_