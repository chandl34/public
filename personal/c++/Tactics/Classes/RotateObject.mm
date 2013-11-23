/*
 *  MovableObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "RotateObject.h"


RotateObject::RotateObject(const ObjType& ot, const Dir& d, GLshort is, 
						   const HP& mhp)
: Object(ot, is, mhp)
, _dir(d)
{
	
}

RotateObject::~RotateObject()
{
	
}


//--- GENERAL ---//
GLshort RotateObject::getModelType() const
{
	return ROTATE_MODEL;
}

bool RotateObject::isDynamic() const
{
	return true;
}

GLshort RotateObject::getDir() const
{ 
	return _dir;
}

double RotateObject::getDir(GLshort c) const
{
	return _ray.getDir(c);
}
