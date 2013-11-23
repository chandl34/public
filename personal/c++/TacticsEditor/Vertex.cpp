/*
 *  Vertex.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vertex.h"


Vertex::Vertex(double x, double y, double z) : Geometry(x, y, z){
	projected = false;
}


//--- GENERAL ---//
void Vertex::setLoc(double x, double y, double z){
	setValue(x, y, z);
}

double Vertex::getLoc(GLshort i) const{
	return val[i];
}


//--- MORPH ---//
void Vertex::flip(){
	double temp = val[X];
	val[X] = val[Y];
	val[Y] = temp;
}

void Vertex::shift(double x, double y, double z){
	val[X] += x;
	val[Y] += y;
	val[Z] += z;
}


// TESTING
void Vertex::print() const{
	printf("(%f, %f, %f)\n", val[X], val[Y], val[Z]);
}