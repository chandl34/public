/*
 *  Triangle.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Triangle.h"


Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2){
	vert[0] = v0;
	vert[1] = v1;
	vert[2] = v2;
}


//--- GENERAL ---//
const Vertex& Triangle::getVert(GLshort i) const{
	return vert[i];
}

Vertex& Triangle::getVert(GLshort i){
	return vert[i];
}