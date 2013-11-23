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
#include "Vertex.h"


class Ray{
public:
	Ray();
	Ray(const Vertex&, const Vertex&);
	Ray(const Vertex&, const Vector&);
	
	void setRay(const Vertex&, const Vertex&);
	void setRay(const Vertex&, const Vector&);
	
	void setLoc(double, double, double);	
	double getLoc(GLshort) const;
	const Vertex& getLoc() const;				// BAD PRACTICE -- REMOVE!!!
	
	void setDir(double, double, double);	
	double getDir(GLshort) const;	
	const Vector& getDir() const;				// BAD PRACTICE -- REMOVE!!!
	
	double size() const;
	
	//--- MORPHS ---//
	void normalize();
	void step();
		
private:	
	Vertex origin;
	Vector dir;
};

#endif

