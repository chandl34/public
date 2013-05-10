/*
 *  Object.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"

#include "Model.h"
#include "Object.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


Object* Object::create(const ObjType& ot, GLshort is)
{
	Object* o = new Object(ot, is);
	o->image = ImageStorage::getConstImage(ot, is);
	o->model = ModelStorage::getConstModel(ot);	
	return o;
}

Object::Object(const ObjType& ot, GLshort is) 
: Icon(NULL)
, objectType(ot)
, ray(Vertex(), Vector())
{	
	index = is;
}

Object::~Object()
{

}


//--- GENERAL ---//
void Object::setCoord3D(double x, double y, double z)
{
	ray.setLoc(x, y, z);
	
	double ox, oy;
	ox = getGlobalLoc(X, Dimension(MINIMUM)) - getGlobalLoc(Y, Dimension(MAXIMUM)) + MAP_OFFSET[X];
	oy = (getGlobalLoc(X, Dimension(MINIMUM)) + getGlobalLoc(Y, Dimension(MINIMUM))) / 2.0 + MAP_OFFSET[Y];
	oy += (getGlobalLoc(Z, Dimension(MINIMUM))) * Z_MOD;
	
	setOffset(ox, oy);
}

double Object::getCoord3D(GLshort c) const
{
	return ray.getLoc(c);
}

void Object::resetCoord3D()
{
	setCoord3D(ray.getLoc(X), ray.getLoc(Y), ray.getLoc(Z));
}

GLshort Object::getModelType() const
{
	return CONST_MODEL;
}

GLshort Object::getObjType() const
{
	return objectType;
}

const Model& Object::getModel() const
{
	return *model;
}

GLshort Object::getIndex() const
{
	return index;
}


//---- DRAW ----//
void Object::draw(bool step, bool bl, GLuint* tn, GLuint* tc, GLuint* tv)
{
	Icon::draw(step, tn, tc, tv);
}

