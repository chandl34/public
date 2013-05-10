/*
 *  Geometry.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 2/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Geometry.h"


Geometry::Geometry(double x, double y, double z){
	setValue(x, y, z);
}

Geometry::~Geometry(){
	
}


//--- GENERAL ---//
void Geometry::setValue(double x, double y, double z){
	val[X] = x;
	val[Y] = y;
	val[Z] = z;
}

double Geometry::dot(const Geometry& f) const{
	return dot(f.val[X], f.val[Y], f.val[Z]);
}

double Geometry::dot(double x, double y, double z) const{
	return val[X]*x + val[Y]*y + val[Z]*z;
}


//--- MORPH ---//
void Geometry::rotateX(double xRot){
	double c = cos(xRot);
	double s = sin(xRot);	
	double y = val[Y];
	
	val[Y] = y*c + val[Z]*s;
	val[Z] = -y*s + val[Z]*c;
}

void Geometry::rotateY(double yRot){
	double c = cos(yRot);
	double s = sin(yRot);	
	double x = val[X];
	
	val[X] = x*c + val[Z]*s;
	val[Z] = -x*s + val[Z]*c;
}

void Geometry::rotateZ(double zRot){
	double c = cos(zRot);
	double s = sin(zRot);	
	double x = val[X];
	
	val[X] = x*c + val[Y]*s;
	val[Y] = -x*s + val[Y]*c;
}