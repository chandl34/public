/*
 *  Vertex.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vertex.h"


Vertex::Vertex(){
	setLoc(0, 0, 0);
}

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z){
	setLoc(x, y, z);
}

Vertex::~Vertex(){
	
}


//--- GENERAL ---//
void Vertex::setLoc(GLfloat x, GLfloat y, GLfloat z){
	loc[X] = x;
	loc[Y] = y;
	loc[Z] = z;
}

GLfloat Vertex::getLoc(GLshort i) const{
	return loc[i];
}


//--- MORPH ---//
void Vertex::flip(){
	GLfloat temp = loc[X];
	loc[X] = loc[Y];
	loc[Y] = temp;
}

void Vertex::shift(GLfloat x, GLfloat y){
	loc[X] += x;
	loc[Y] += y;
}

void Vertex::rotateZ(GLfloat t){
	GLfloat c = cos(t);
	GLfloat s = sin(t);	
	GLfloat x = loc[X];
	
	loc[X] = loc[X]*c + loc[Y]*s;
	loc[Y] = -x*s + loc[Y]*c;
}
