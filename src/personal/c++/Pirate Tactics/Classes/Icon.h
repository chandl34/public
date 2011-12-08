/*
 *  Icon.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ICON_H_
#define ICON_H_

#include "Image.h"

class Icon : public Drawable{
public:
	Icon(Image*);
	Icon(Image*, const Coord2d<GLfloat>&);
	virtual ~Icon();	
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;	
	virtual void setOffset(GLfloat, GLfloat);
	const Coord2d<GLfloat>& getOffset() const;
	GLfloat getOffset(GLshort) const;
	
	//---- DRAW ----//
	virtual void draw(bool);
	
protected:
	//--- GENERAL ---//
	Image* image;
	
	// SCREEN OFFSET //
	Coord2d<GLfloat> offset;
};

#endif
