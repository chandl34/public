/*
 *  Movable.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Movable.h"


Movable::Movable(const Coord2d<double>& os)
: _offset(os)
{
	
}

Movable::~Movable()
{
	
}


//---- GENERAL ----//
const Coord2d<double>& Movable::getOffset() const
{
	return _offset;
}

double Movable::getOffset(GLshort i) const
{
	return _offset[i];
}

void Movable::setOffset(double x, double y)
{
	_offset[X] = x;
	_offset[Y] = y;
}

void Movable::setOffset(Movable* m)
{
	if(m == NULL)
		setOffset(-500, -500);
	else
		setOffset(m->getOffset(X), m->getOffset(Y));
}
