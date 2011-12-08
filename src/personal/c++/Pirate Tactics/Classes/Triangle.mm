/*
 *  Triangle.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Triangle.h"

Triangle::Triangle(GLshort f0, GLshort f1, GLshort f2){
	vert[0] = f0;
	vert[1] = f1;
	vert[2] = f2;
}

Triangle::~Triangle(){	
	
}


GLshort Triangle::getVert(GLshort f) const{
	return vert[f];
}