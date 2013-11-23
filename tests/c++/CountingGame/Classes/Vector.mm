/*
 *  Vector.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector.h"

#include "Vertex.h"


Vector::Vector(double x, double y, double z){
	setDir(x, y, z);
}

// Vector = VertexT - VertexO
Vector::Vector(const Vertex& t, const Vertex& o){
	setDir(t, o);
}

// Vector = VectorA * VectorB -- cross product
Vector::Vector(const Vector& a, const Vector& b){
	setDir(a, b);
}


//--- GENERAL ---//
void Vector::setDir(const Vertex& t, const Vertex& o){
	for(GLshort i = 0; i < 3; ++i)
		val[i] = t.getLoc(i) - o.getLoc(i);
}

void Vector::setDir(const Vector& a, const Vector& b){
	val[X] = a.val[Y]*b.val[Z] - a.val[Z]*b.val[Y];
	val[Y] = a.val[Z]*b.val[X] - a.val[X]*b.val[Z];
	val[Z] = a.val[X]*b.val[Y] - a.val[Y]*b.val[X];	
}

void Vector::setDir(double x, double y, double z){
	val[X] = x;
	val[Y] = y;
	val[Z] = z;
}

double Vector::getDir(GLshort i) const{
	return val[i];
}

double Vector::size() const{
	return sqrt(dot(*this));
}


//--- MORPHS ---//
void Vector::normalize(){
	double s = size();
	for(GLshort i = 0; i < 3; ++i)
		val[i] = val[i]/s;
}


// TESTING
void Vector::print() const{
	printf("<%f, %f, %f>\n", val[X], val[Y], val[Z]);
}