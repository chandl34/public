/*
 *  Ray.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ray.h"
#include "LevelMap.h"


Ray::Ray(){
	
}

Ray::Ray(const Object* t, const Object* o){
	setRay(t, o);
}

Ray::~Ray(){
	
}


void Ray::setRay(const Object* t, const Object* o){
	origin.setLoc(o->getCoord3D(X) + o->getRange(X, MID_C),
				  o->getCoord3D(Y) + o->getRange(Y, MID_C),
				  o->getCoord3D(Z) + o->getRange(Z, MID_C));
	
	dir.setDir(t->getCoord3D(X) + t->getRange(X, MID_C) - origin.getLoc(X),
			   t->getCoord3D(Y) + t->getRange(Y, MID_C) - origin.getLoc(Y),
			   t->getCoord3D(Z) + t->getRange(Z, MID_C) - origin.getLoc(Z));
}

void Ray::setLoc(GLfloat x, GLfloat y, GLfloat z){
	origin.setLoc(x, y, z);
}

void Ray::setDir(GLfloat x, GLfloat y, GLfloat z){
	dir.setDir(x, y, z);
}


GLfloat Ray::getLoc(GLshort i) const{
	return origin.getLoc(i);
}

GLfloat Ray::getDir(GLshort i) const{
	return dir.getDir(i);
}

const Vector& Ray::getDir() const{
	return dir;
}

const Vertex& Ray::getLoc() const{
	return origin;
}


void Ray::normalize(){
	dir.normalize();
}


Object* Ray::testFlight(GLfloat& lifespan) const{
	// Do a trial run to find the bullet's lifespan
	//double timer = [[NSDate date] timeIntervalSince1970];
	lifespan = -1;
	Ray tRay(*this);
	GridBlock* ogb = LevelMap::getBlockBy3D(tRay.getLoc(X), tRay.getLoc(Y));  // currently assumes ogb doesn't start at NULL -- shouldn't happen
	Object* o = ogb->detectHit(tRay, lifespan, true);
	
	if(o == NULL){	
		Object* ot;
		GLshort t = 0;
		GridBlock* ngb;
		while(lifespan < 0){					
			ngb = LevelMap::getBlockBy3D(tRay.getLoc(X) + tRay.getDir(X), 
										 tRay.getLoc(Y) + tRay.getDir(Y));
			if(ngb == ogb)
				t++;
			else{
				if(ngb == NULL)
					break;
				ogb = ngb;
				ot = ogb->detectHit(tRay, lifespan, false);
				if(ot != NULL)
					o = ot;
			}
		
			tRay.setLoc(tRay.getLoc(X) + tRay.getDir(X),
						tRay.getLoc(Y) + tRay.getDir(Y), 
						tRay.getLoc(Z) + tRay.getDir(Z));
		}
		if(lifespan < 0)
			lifespan++;	
		lifespan += t;
	}
	
	//cout << "Time: " << [[NSDate date] timeIntervalSince1970] - timer << endl;
	cout << "Lifespan: " << lifespan << endl;
	return o;
}
