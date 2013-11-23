/*
 *  OffsetBase.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "OffsetBase.h"


OffsetBase::OffsetBase(const Coord2d<double>& os)
: _offset(os)
{
	
}

OffsetBase::~OffsetBase()
{
	
}


//---- GENERAL ----//
const Coord2d<double>& OffsetBase::getOffset() const
{
	return _offset;
}

double OffsetBase::getOffset(GLshort i) const
{
	return _offset[i];
}

void OffsetBase::setOffset(double x, double y)
{
	_offset[X] = x;
	_offset[Y] = y;
}
