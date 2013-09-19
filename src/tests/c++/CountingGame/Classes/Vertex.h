/*
 *  Vertex.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Geometry.h"


class Vertex : public Geometry{
public:	
	Vertex(double x = 0.0, double y = 0.0, double z = 0.0);
		
	//--- GENERAL ---//
	void setLoc(double, double, double);	
	double getLoc(GLshort) const;
		
	//--- MORPH ---//
	void flip();							// Mirrors vertex by swapping X and Y
	void shift(double x = 0.0, 
			   double y = 0.0, 
			   double z = 0.0);
	
	// TESTING
	void print() const;
	
private:
	bool projected;
};

#endif

