/*
 *  BaseIcon.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "BaseIcon.h"


BaseIcon::BaseIcon(const Coord2d<double>& offset)
: Touchable(false)
, _offset(offset)
{
	_enabled = true;
}

BaseIcon::~BaseIcon()
{
	
}


//--- GENERAL ---//
const Coord2d<double>& BaseIcon::getOffset() const
{
	return _offset;
}

double BaseIcon::getOffset(GLshort a) const
{
	return _offset[a];
}

void BaseIcon::setOffset(double x, double y)
{
	_offset[X] = x;
	_offset[Y] = y;
}

void BaseIcon::enable(bool e)
{
	_enabled = e;
}



// Non-member Functions
void enable(BaseIcon* icon, void* arg)
{
	icon->enable((bool)arg);
}



