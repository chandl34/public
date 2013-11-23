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
						   const HP& mhp) : Object(ot, is, mhp),
										    dir(d){
}

RotateObject::~RotateObject(){
	
}


//--- GENERAL ---//
const Dir& RotateObject::getDir() const{ 
	return dir;
}

GLfloat RotateObject::getDir(GLshort c) const{
	return ray.getDir(c);
}
