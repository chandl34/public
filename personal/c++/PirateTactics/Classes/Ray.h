/*
 *  Ray.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RAY_H_
#define RAY_H_

#include "Vector.h"


class Object;

class Ray{
public:
	Ray();
	Ray(const Object*, const Object*);
	~Ray();
		
	void setRay(const Object*, const Object*);
	
	void setLoc(GLfloat, GLfloat, GLfloat);	
	void setDir(GLfloat, GLfloat, GLfloat);
	
	GLfloat getLoc(GLshort) const;
	GLfloat getDir(GLshort) const;
	
	const Vector& getDir() const;
	const Vertex& getLoc() const;
	
	void normalize();
	
	Object* testFlight(GLfloat&) const;
		
private:	
	Vertex origin;
	Vector dir;
};

#endif

