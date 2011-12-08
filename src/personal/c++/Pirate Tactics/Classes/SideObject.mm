/*
 *  SideObject.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SideObject.h"
#include "ModelContainer.h"


SideObject* SideObject::create(const ObjType& ot, const Side& s, GLshort is, 
							   const HP& mhp){	
	SideObject* o = new SideObject(ot, s, is, mhp);	
	o->image = ModelContainer::getSideImage(ot, s, is);
	o->model = ModelContainer::getSideModel(ot, s);
	return o;
}

SideObject::SideObject(const ObjType& ot, const Side& s, GLshort is, 
					   const HP& mhp) : Object(ot, is, mhp),
										side(s){
}


SideObject::~SideObject(){}


//--- GENERAL ---//
const Side& SideObject::getSide() const{
	return side;
}
