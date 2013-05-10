/*
 *  SideObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SideObject.h"

#include "ImageStorage.h"
#include "Math.h"
#include "ModelStorage.h"


SideObject* SideObject::create(const ObjType& ot, const Side& s, GLshort is)
{	
	SideObject* o = new SideObject(ot, s, is);	
	o->image = ImageStorage::getSideImage(ot, s, is);
	o->model = ModelStorage::getSideModel(ot, s);
	return o;
}

SideObject::SideObject(const ObjType& ot, const Side& s, GLshort is) 
: Object(ot, is)
, side(s)
{
	
}

SideObject::~SideObject(){}


//--- GENERAL ---//
GLshort SideObject::getModelType() const
{
	return SIDE_MODEL;
}

GLshort SideObject::getSide() const
{
	return side;
}

//---- DRAW ----//
void SideObject::draw(bool step, bool bl, GLuint* tn, GLuint* tc, GLuint* tv)
{
	if(bl)
		glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	
	Object::draw(step, bl, tn, tc, tv);
	
	if(bl)
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}