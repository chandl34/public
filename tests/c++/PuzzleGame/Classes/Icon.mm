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
void Icon::setImage(Image* image)
{
	_image = image;
}

const Size2d<GLshort>& Icon::getSize() const
{
	return _image->getSize();
}

GLshort Icon::getSize(GLshort a) const
{
	return _image->getSize(a);
}

GLshort Icon::getTexOffset(GLshort a)
{
	return _image->getTexOffset(a);
}


//--- TOUCH ---//
bool Icon::isTouching(const Coord2d<GLshort>& p)
{
	return pointInQuad(p, getOffset(), getSize());
}

void Icon::push(GLshort, const Coord2d<GLshort>&){}
void Icon::move(GLshort, const Coord2d<GLshort>&){}
bool Icon::release(GLshort, const Coord2d<GLshort>&){return false;}


//---- DRAW ----//
void Icon::draw(bool step)
{
	if(_enabled && _image != NULL){			
		glLoadIdentity();	
		glTranslatef(_offset[X], _offset[Y], 0);
		
		_image->draw(step);		
	}
}

