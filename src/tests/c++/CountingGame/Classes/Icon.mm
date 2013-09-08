/*
 *  Icon.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Icon.h"

#include "Image.h"

#include "HitTest.h"


Icon::Icon(Image* image, const Coord2d<double>& offset)
: BaseIcon(offset)
{
	_image = image;
}

Icon::~Icon(){
	
}


//--- GENERAL ---//
const Size2d<GLshort>& Icon::getSize() const
{
	return _image->getSize();
}

GLshort Icon::getSize(GLshort a) const
{
	return _image->getSize(a);
}

void Icon::setImage(Image* image)
{
	_image = image;
}


//--- TOUCH ---//
bool Icon::isTouching(const Coord2d<GLshort>& p)
{
	return pointInQuad(p, getOffset(), getSize());
}


//---- DRAW ----//
void Icon::draw(bool step)
{
	if(_enabled && _image != NULL){			
		glLoadIdentity();	
		glTranslatef(_offset[X], _offset[Y], 0);
		
		_image->draw(step);		
	}
}

