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
#include "ModelStorage.h"


SideObject* SideObject::create(const ObjType& ot, const Side& s, GLshort is, 
							   const HP& mhp)
{	
	SideObject* o = new SideObject(ot, s, is, mhp);	
	o->_image = ImageStorage::getSideImage(ot, s, is);
	o->_model = ModelStorage::getSideModel(ot, s);
	return o;
}

SideObject::SideObject(const ObjType& ot, const Side& s, GLshort is, 
					   const HP& mhp)
: Object(ot, is, mhp)
, _side(s)
{
	
}

SideObject::~SideObject()
{

}


//--- GENERAL ---//
GLshort SideObject::getModelType() const
{
	return SIDE_MODEL;
}

GLshort SideObject::getSide() const
{
	return _side;
}

//---- DRAW ----//
void SideObject::draw(bool step, TexAttr* ta)
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
	Object::draw(step, ta);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}