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

#include "Vertex.h"

class Vector{
public:
	Vector();
	Vector(GLfloat, GLfloat, GLfloat);
	Vector(const Vertex&, const Vertex&);	// Vt - Vo
	Vector(const Vector&, const Vector&);	// Cross product
	~Vector();
	
	void setDir(GLfloat, GLfloat, GLfloat);
	
	GLfloat getDir(GLshort) const;
	
	void normalize();
	
	GLfloat dot(const Vector&) const;
	GLfloat dot(GLfloat, GLfloat, GLfloat) const;
	
private:	
	GLfloat dir[3];
};

#endif

