/*
 *  Component.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Component.h"

#include "HitTest.h"


Component::Component(const Coord2d<double>& os,
					 const Size2d<GLshort>& size)
: OffsetBase(os)
, SizeBase(size)
, Touchable(false)
{
	
}

Component::~Component()
{
	
}


//--- TOUCH ---//
bool Component::isTouching(const Coord2d<GLshort>& p)
{
	return pointInQuad(p, _offset, _size);
}


bool Component::push(GLshort t, const Coord2d<GLshort>& p)
{
	return false;
}

bool Component::move(GLshort t, const Coord2d<GLshort>& p)
{
	return false;
}

bool Component::release(GLshort t, const Coord2d<GLshort>& p)
{
	return false;
}	


