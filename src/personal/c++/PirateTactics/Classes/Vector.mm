/*
 *  Vector.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.h"


Vector::Vector(){
	setDir(0, 0, 0);
}

Vector::Vector(GLfloat x, GLfloat y, GLfloat z){
	setDir(x, y, z);
}

// Vector = VertexT - VertexO
Vector::Vector(const Vertex& t, const Vertex& o){
	for(GLshort i = 0; i < 3; i++)
		dir[i] = t.getLoc(i) - o.getLoc(i);
}

// Vector = VectorA * VectorB -- cross product
Vector::Vector(const Vector& a, const Vector& b){
	dir[X] = a.getDir(Y)*b.getDir(Z) - a.getDir(Z)*b.getDir(Y);
	dir[Y] = a.getDir(Z)*b.getDir(X) - a.getDir(X)*b.getDir(Z);
	dir[Z] = a.getDir(X)*b.getDir(Y) - a.getDir(Y)*b.getDir(X);	
}

Vector::~Vector(){
	
}


void Vector::setDir(GLfloat x, GLfloat y, GLfloat z){
	dir[X] = x;
	dir[Y] = y;
	dir[Z] = z;
}

GLfloat Vector::getDir(GLshort i) const{
	return dir[i];
}


void Vector::normalize(){
	GLfloat size = sqrt(dir[X]*dir[X] + dir[Y]*dir[Y] + dir[Z]*dir[Z]);
	for(GLshort i = 0; i < 3; i++)
		dir[i] = dir[i]/size;
}


GLfloat Vector::dot(const Vector& v) const{
	return dir[X]*v.getDir(X) + dir[Y]*v.getDir(Y) + dir[Z]*v.getDir(Z);
}

GLfloat Vector::dot(GLfloat x, GLfloat y, GLfloat z) const{
	return dir[X]*x + dir[Y]*y + dir[Z]*z;
}
