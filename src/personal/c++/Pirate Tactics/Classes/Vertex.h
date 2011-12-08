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

#include "Include.h"

class Vertex{
public:
	Vertex();
	Vertex(GLfloat, GLfloat, GLfloat);
	~Vertex();
	
	//--- GENERAL ---//
	void setLoc(GLfloat, GLfloat, GLfloat);
	
	GLfloat getLoc(GLshort) const;
	
	//--- MORPH ---//
	void flip();
	void shift(GLfloat, GLfloat);
	void rotateZ(GLfloat);
	
private:	
	GLfloat loc[3];
};

#endif

