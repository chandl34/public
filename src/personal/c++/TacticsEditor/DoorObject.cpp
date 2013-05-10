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
										 GLshort is)
{	
	DoorObject* o = new DoorObject(ot, si, inn, hin, is);	
	o->image = ImageStorage::getDoorImage(ot, si, inn, hin, o->open, is);
	o->model = ModelStorage::getDoorModel(ot, si, inn, hin, o->open);
	return o;
}

DoorObject::DoorObject(const ObjType& ot, 
							  const Side& si, 
							  const Inner& inn, const Hinge& hin, 
							  GLshort is) 
: SideObject(ot, si, is)
, inner(inn)
, hinge(hin)
, open(CLOSED)
{	
	
}

DoorObject::~DoorObject(){
	
}


//-- GENERAL --//
GLshort DoorObject::getModelType() const
{
	return DOOR_MODEL;
}

GLshort DoorObject::isInner() const
{
	return inner;
}

GLshort DoorObject::getHinge() const
{
	return hinge;
}

GLshort DoorObject::isOpen() const
{
	return open;
}


void DoorObject::toggleDoor(){
	open = !open;
	
	image = ImageStorage::getDoorImage(objectType, side, inner, hinge, open, 0);
	model = ModelStorage::getDoorModel(objectType, side, inner, hinge, open);
	
	setCoord3D(getCoord3D(X), getCoord3D(Y), getCoord3D(Z));	
}
