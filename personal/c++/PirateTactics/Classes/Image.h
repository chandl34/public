/*
 *  Image.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "Drawable.h"

class Image : public Drawable{
public:
	Image(const Size2d<GLshort>&, GLshort);
	Image(const Size2d<GLshort>&, const Size2d<GLshort>&, GLshort);
	~Image();
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;
	
	//---- DRAW ----//
	void draw(bool);	
	
private:	
	//--- GENERAL ---//
	GLshort texName;
	Size2d<GLshort> size;
	const GLshort* vert;
	const GLfloat* texCoord;
};

#endif

