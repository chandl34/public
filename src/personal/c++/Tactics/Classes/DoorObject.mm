/*
 *  DoorObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "DoorObject.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


DoorObject* DoorObject::create(const ObjType& ot, 
										 const Side& si, 
										 const Inner& inn, const Hinge& hin, 
										 GLshort is, 
										 const HP& mhp)
{	
	DoorObject* o = new DoorObject(ot, si, inn, hin, is, mhp);	
	o->_image = ImageStorage::getDoorImage(ot, si, inn, hin, o->_open, is);
	o->_model = ModelStorage::getDoorModel(ot, si, inn, hin, o->_open);
	return o;
}

DoorObject::DoorObject(const ObjType& ot, 
							  const Side& si, const Inner& inn, const Hinge& hin, 
							  GLshort is, 
							  const HP& mhp) 
: SideObject(ot, si, is, mhp)
, _inner(inn)
, _hinge(hin)
, _open(CLOSED)
{	
	
}

DoorObject::~DoorObject()
{
	
}


//-- GENERAL --//
GLshort DoorObject::getModelType() const
{
	return DOOR_MODEL;
}

bool DoorObject::isDynamic() const
{
	return true;
}

bool DoorObject::isInner() const
{
	return _inner;
}

GLshort DoorObject::getHinge() const
{
	return _hinge;
}

bool DoorObject::isOpen() const
{
	return _open;
}

void DoorObject::toggleDoor()
{
	_open = !_open;
	
	_image = ImageStorage::getDoorImage(_objectType, _side, _inner, _hinge, _open, 0);
	_model = ModelStorage::getDoorModel(_objectType, _side, _inner, _hinge, _open);
	
	setCoord3D(getCoord3D(X), getCoord3D(Y), getCoord3D(Z));	
}