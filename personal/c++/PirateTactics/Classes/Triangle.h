/*
 *  Triangle.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Include.h"

class Triangle{
public:
	Triangle(GLshort, GLshort, GLshort);
	~Triangle();
	
	GLshort getVert(GLshort) const;
			
private:	
	GLshort vert[3];
};

#endif

