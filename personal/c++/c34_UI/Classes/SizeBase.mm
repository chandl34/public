/*
 *  SizeBase.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "SizeBase.h"


SizeBase::SizeBase(const Size2d<GLshort>& size)
: _size(size)
{
	
}

SizeBase::~SizeBase()
{
	
}


//---- GENERAL ----//
const Size2d<GLshort>& SizeBase::getSize() const
{
	return _size;
}

double SizeBase::getSize(GLshort c) const
{
	return _size[c];
}

void SizeBase::setSize(GLshort x, GLshort y)
{
	_size[X] = x;
	_size[Y] = y;
}
