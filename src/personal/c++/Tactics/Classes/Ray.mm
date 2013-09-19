/*
 *  Ray.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ray.h"


Ray::Ray(){
	
}

Ray::Ray(const Vertex& t, const Vertex& o){
	setRay(t, o);
}

Ray::Ray(const Vertex& vert, const Vector& vect){
	setRay(vert, vect);
}

void Ray::setRay(const Vertex& t, const Vertex& o){
	origin = o;
	dir.setDir(t, o);
}

void Ray::setRay(const Vertex& vert, const Vector& vect){
	origin = vert;
	dir = vect;
}

void Ray::setLoc(double x, double y, double z){
	origin.setLoc(x, y, z);
}
double Ray::getLoc(GLshort i) const{
	return origin.getLoc(i);
}
const Vertex& Ray::getLoc() const{
	return origin;
}

void Ray::setDir(double x, double y, double z){
	dir.setDir(x, y, z);
}
double Ray::getDir(GLshort i) const{
	return dir.getDir(i);
}
const Vector& Ray::getDir() const{
	return dir;
}

double Ray::size() const{
	return dir.size();
}


//--- MORPHS ---//
void Ray::normalize(){
	dir.normalize();
}

void Ray::step(){
	origin.setLoc(origin.getLoc(X) + dir.getDir(X),
				  origin.getLoc(Y) + dir.getDir(Y),
				  origin.getLoc(Z) + dir.getDir(Z));
}
