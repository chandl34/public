/*
 *  Object.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"

#include "Hit.h"
#include "Model.h"
#include "Object.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


Object* Object::create(const ObjType& ot, GLshort is, 
							  const HP& mhp)
{
	Object* o = new Object(ot, is, mhp);
	o->_image = ImageStorage::getConstImage(ot, is);
	o->_model = ModelStorage::getConstModel(ot);	
	return o;
}

Object::Object(const ObjType& ot, GLshort is, 
					const HP& mhp) 
: Icon(NULL)
, _objectType(ot)
, _animSet(AnimationSet(ImageStorage::getImageSet(is)))
, _ray(Vertex(), Vector())
{	
	_index = is;
	_maxHP = mhp;
	_currHP = mhp;
}

Object::~Object()
{
	
}


//--- GENERAL ---//
void Object::setCoord3D(double x, double y, double z)
{
	_ray.setLoc(x, y, z);
	
	double ox, oy;
	ox = getGlobalLoc(X, Dimension(MINIMUM)) - getGlobalLoc(Y, Dimension(MAXIMUM)) + MAP_OFFSET[X];
	oy = (getGlobalLoc(X, Dimension(MINIMUM)) + getGlobalLoc(Y, Dimension(MINIMUM))) / 2.0 + MAP_OFFSET[Y];
	oy += (getGlobalLoc(Z, Dimension(MINIMUM))) * Z_MOD;
	
	setOffset(ox, oy);
}

double Object::getCoord3D(GLshort c) const
{
	return _ray.getLoc(c);
}

void Object::resetCoord3D()
{
	setCoord3D(_ray.getLoc(X), _ray.getLoc(Y), _ray.getLoc(Z));
}


GLshort Object::getModelType() const
{
	return CONST_MODEL;
}

GLshort Object::getObjType() const
{
	return _objectType;
}

GLshort Object::getIndex() const
{
	return _index;
}

bool Object::isUnit() const
{
	return false;
}

bool Object::isDynamic() const
{
	return false;
}

const Model& Object::getModel() const
{
	return *_model;
}


//--- ACTION ---//
GLshort Object::update()
{
	if(_currHP <= 0)
		return DIED;
	
	return NO_CHANGE;
}


//--- COMBAT ---//
void Object::takeDamage(GLshort section, GLshort damage)
{
	printf("Using object takeDamage method\n");
}


//-- HIT DETECTION --//
bool Object::detectHit(const Ray& r, Hit& hit)
{
	if(_model == NULL || !_model->detectHit(r, _ray.getLoc(), hit))
		return false;
	hit.setObjectHit(this);
	return true;
}


//-- PATHING --//
bool Object::blocks(GLshort dir) const
{
	if(_model == NULL)
		return false;
	return _model->blocks(dir);
}

bool Object::isIdle() const
{
	return true;
}


//--- STATS ---//
GLshort Object::getHP() const
{
	return _currHP;
}

void Object::setHP(GLshort hp)
{
	_currHP = hp;
}

GLshort Object::getMaxHP() const
{
	return _maxHP;
}
