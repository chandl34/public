/*
 *  Object.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"
#include "Camera.h"
#include "ModelContainer.h"


Object* Object::create(const ObjType& ot, GLshort is, 
					   const HP& mhp){
	Object* o = new Object(ot, is, mhp);
	o->image = ModelContainer::getConstImage(ot, is);
	o->model = ModelContainer::getConstModel(ot);	
	return o;
}

Object::Object(const ObjType& ot, GLshort is, 
			   const HP& mhp) : Icon(NULL), 
								objectType(ot),
								maxHP(mhp), currHP(mhp){	
	//--- GENERAL ---//
	imageSet = is;	
}

Object::~Object(){}


//--- GENERAL ---//
void Object::setCoord3D(GLfloat x, GLfloat y, GLfloat z){
	ray.setLoc(x, y, z);
		
	GLfloat ox, oy;
	ox = (x - y + getRange(X, MIN_C) - getRange(Y, MAX_C)) + MAP_OFFSET[X];
	oy = (x + y + getRange(X, MIN_C) + getRange(Y, MIN_C))/2.0f + MAP_OFFSET[Y];
	oy += (z + getRange(Z, MIN_C))*Z_MOD;
	
	setOffset(ox, oy);
}

GLfloat Object::getCoord3D(GLshort c) const{
	return ray.getLoc(c);
}

bool Object::isUnit(){
	return false;
}


//-- HIT DETECTION --//
bool Object::detectHit(const Ray& r, GLfloat& t) const{
	if(model == NULL)
		return false;
	return model->detectHit(r, ray.getLoc(), t);
}


//-- PATHING --//
bool Object::blocks(GLshort dir) const{
	if(model == NULL)
		return false;
	return model->blocks(dir);
}

bool Object::isMoving() const{
	return false;
}

