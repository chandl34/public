/*
 *  DoorObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "DoorObject.h"
#include "ModelContainer.h"


DoorObject* DoorObject::create(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, GLshort is, 
							   const HP& mhp){	
	DoorObject* o = new DoorObject(ot, si, inn, hin, is, mhp);	
	o->image = ModelContainer::getDoorImage(ot, si, inn, hin, o->open, is);
	o->model = ModelContainer::getDoorModel(ot, si, inn, o->open, hin);
	return o;
}

DoorObject::DoorObject(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, GLshort is, 
					   const HP& mhp) : SideObject(ot, si, is, mhp),
										inner(inn), hinge(hin), open(CLOSED){	
}

DoorObject::~DoorObject(){
	
}


//-- GENERAL --//
bool DoorObject::isOpen() const{
	return open;
}

bool DoorObject::isInner() const{
	return inner;
}

void DoorObject::toggleDoor(){
	open = !open;
	
	image = ModelContainer::getDoorImage(objectType, side, inner, hinge, open, imageSet);
	model = ModelContainer::getDoorModel(objectType, side, inner, hinge, open);
	
	setCoord3D(getCoord3D(X), getCoord3D(Y), getCoord3D(Z));	// Updates offset
}
