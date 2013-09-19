/*
 *  Vector.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "Geometry.h"

class Vertex;


class Vector : public Geometry{
public:
	Vector(double x = 0.0, double y = 0.0, double z = 0.0);
	Vector(const Vertex&, const Vertex&);	// Vt - Vo
	Vector(const Vector&, const Vector&);	// Cross product
	
	//--- GENERAL ---//
	void setDir(const Vertex&, const Vertex&);
	void setDir(const Vector&, const Vector&);	
	void setDir(double, double, double);	
	double getDir(GLshort) const;
	
	double size() const;
		
	//--- MORPHS ---//
	void normalize();
	
	// TESTING
	void print() const;
};

#endif

