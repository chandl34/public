/*
 *  Bullet.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Bullet.h"
#include "Camera.h"
#include "GridBlock.h"
#include "LevelMap.h"
#include "ModelContainer.h"


Bullet* Bullet::create(const ObjType& ot, const Dir& d, GLshort is, 
					   const HP& mhp, 
					   const Object* t, const Object* o){
	Bullet* b = new Bullet(ot, d, is, mhp, t, o);	
	b->image = ModelContainer::getRotateImage(ot, d, is);
	b->model = ModelContainer::getRotateModel(ot, d);
	return b;
}

Bullet::Bullet(const ObjType& ot, const Dir& d, GLshort is, 
			   const HP& mhp, 
			   const Object* t, const Object* o) : RotateObject(ot, d, is, mhp){
	ray.setRay(t, o);
	ray.normalize();
	hit = ray.testFlight(lifespan);
}

Bullet::~Bullet(){
	
}


//--- GENERAL ---//
GLshort Bullet::update(){	
	setCoord3D(ray.getLoc(X) + ray.getDir(X), 
			   ray.getLoc(Y) + ray.getDir(Y),
			   ray.getLoc(Z) + ray.getDir(Z));
	lifespan--;
	return lifespan > 0;
}
